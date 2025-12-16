#!/bin/bash

SEGFAULT_FILE="segfault_commands.txt"
> "$SEGFAULT_FILE"

test_command() {
    local cmd="$1"
    echo "Testing: $cmd" >&2
    
    # Run with timeout and check for segfault
    timeout 2 bash -c "echo '$cmd' | valgrind --leak-check=no --error-exitcode=42 ./minishell 2>&1" | grep -q "SIGSEGV"
    
    if [ $? -eq 0 ]; then
        echo "SEGFAULT: $cmd" >> "$SEGFAULT_FILE"
        echo "  ❌ SEGFAULT" >&2
    else
        echo "  ✓ OK" >&2
    fi
}

echo "=== Testing commands from 0_compare_parsing.sh ===" >&2
test_command '/bin/echo ""$?""'
test_command '/bin/echo $?"42"'
test_command '/bin/echo '\'''\''$?'\'\''"42"'
test_command '/bin/echo '"'"'$USER'"'"
test_command '/bin/echo "'"'"'$USER'"'"'"'
test_command '/bin/echo ""'"'"'$USER'"'"'""'
test_command '/bin/echo '"'"'"'"'"'$USER'"'"'"'"'"
test_command 'echo $"HOME"$USER'
test_command 'echo "exit_code ->$? user ->$USER home -> $HOME"'
test_command 'echo $"HOME"'
test_command 'echo $"42$"'
test_command 'echo "$ "'
test_command 'echo '\''$='\'''
test_command 'echo '\''$ '\'''
test_command 'echo "$?"'
test_command 'echo '\''$?'\'''
test_command 'echo "'"'"'$?'"'"'"'
test_command 'echo \$USER'
test_command 'echo'
test_command 'echo '\'''\'''
test_command 'echo ""'
test_command 'echo '\'''\'' ""'

echo "=== Testing builtins ===" >&2
test_command 'pwd'
test_command 'cd'
test_command 'cd ..'
test_command 'cd .'
test_command 'env | grep HOME'
test_command 'export TEST=123'
test_command 'unset TEST'
test_command 'exit'
test_command 'exit 123'

echo "=== Testing pipes ===" >&2
test_command 'echo 1 | grep 1'
test_command 'cat | cat | cat'
test_command 'ls | wc -l'

echo "=== Testing redirections ===" >&2
test_command 'echo hi >./outfiles/outfile01'
test_command 'cat <./test_files/infile'
test_command 'ls >>./outfiles/outfile01'

echo "=== Testing edge cases ===" >&2
test_command '""'
test_command ''\'''\'''
test_command '$NONEXISTENT'
test_command '$?'
test_command 'echo "$USER"'
test_command 'echo '\''$USER'\'''

echo "=== Testing syntax errors ===" >&2
test_command '|'
test_command '>'
test_command '<'
test_command '>>'
test_command '<<'
test_command '| cat'
test_command 'cat |'
test_command 'cat <'
test_command 'cat >'

echo "=== Testing variables ===" >&2
test_command 'echo $HOME'
test_command 'echo $USER'
test_command 'echo $PATH'
test_command 'echo $PWD'
test_command 'export T=test'
test_command 'echo $T'

echo "" >&2
echo "=== RESULTS ===" >&2
if [ -s "$SEGFAULT_FILE" ]; then
    echo "Found segfaults:" >&2
    cat "$SEGFAULT_FILE"
else
    echo "No segfaults found!" >&2
fi
