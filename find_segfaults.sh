#!/bin/bash

OUTPUT_FILE="segfault_list.txt"
> "$OUTPUT_FILE"

echo "=== Suche nach Segfaults in Minishell ===" >&2
echo "" >&2

# Funktion zum Testen eines Befehls
test_cmd() {
    local cmd="$1"
    local category="$2"
    
    # Escape für echo
    local safe_cmd=$(echo "$cmd" | sed 's/"/\\"/g')
    
    # Test mit timeout
    timeout 1 bash -c "echo \"$safe_cmd\" | ./minishell 2>&1" > /tmp/minishell_test_output.txt 2>&1
    local exit_code=$?
    
    # Check ob Segfault
    if [ $exit_code -eq 139 ] || grep -q "Segmentation fault\|segfault\|SIGSEGV" /tmp/minishell_test_output.txt 2>/dev/null; then
        echo "[$category] $cmd" >> "$OUTPUT_FILE"
        echo "  ❌ SEGFAULT: $cmd" >&2
        return 1
    fi
    
    return 0
}

echo "Testing empty/whitespace commands..." >&2
test_cmd '""' "EMPTY"
test_cmd "''" "EMPTY"
test_cmd '   ' "EMPTY"
test_cmd '' "EMPTY"

echo "Testing pipe edge cases..." >&2
test_cmd '|' "PIPE"
test_cmd '| cat' "PIPE"
test_cmd 'cat |' "PIPE"
test_cmd 'cat | | grep' "PIPE"
test_cmd 'echo | | cat' "PIPE"

echo "Testing redirection edge cases..." >&2
test_cmd '>' "REDIR"
test_cmd '<' "REDIR"
test_cmd '>>' "REDIR"
test_cmd '<<' "REDIR"
test_cmd 'cat <' "REDIR"
test_cmd 'cat >' "REDIR"
test_cmd 'cat >>' "REDIR"
test_cmd 'cat <<' "REDIR"
test_cmd '< <' "REDIR"
test_cmd '> >' "REDIR"

echo "Testing variable expansion..." >&2
test_cmd '$' "VAR"
test_cmd '$$' "VAR"
test_cmd '$NONEXISTENT' "VAR"
test_cmd 'echo $' "VAR"
test_cmd 'echo $$' "VAR"
test_cmd 'echo $NONEXISTENT' "VAR"
test_cmd 'echo "$"' "VAR"
test_cmd 'echo '\''$'\''' "VAR"
test_cmd '$?' "VAR"
test_cmd 'echo $?' "VAR"
test_cmd 'echo "$?"' "VAR"

echo "Testing quote combinations..." >&2
test_cmd 'echo ""' "QUOTE"
test_cmd 'echo '\'''\''' "QUOTE"
test_cmd 'echo "" '\'''\''' "QUOTE"
test_cmd 'echo "'"'"'"' "QUOTE"
test_cmd 'echo '\''""'\''' "QUOTE"

echo "Testing export/unset..." >&2
test_cmd 'export' "BUILTIN"
test_cmd 'export =' "BUILTIN"
test_cmd 'export ""=""' "BUILTIN"
test_cmd 'unset' "BUILTIN"
test_cmd 'unset ""' "BUILTIN"

echo "Testing cd..." >&2
test_cmd 'cd' "BUILTIN"
test_cmd 'cd ""' "BUILTIN"
test_cmd 'cd '\'''\''' "BUILTIN"

echo "Testing heredoc..." >&2
test_cmd '<< EOF' "HEREDOC"
test_cmd '<< ""' "HEREDOC"
test_cmd 'cat << EOF' "HEREDOC"

echo "Testing complex cases..." >&2
test_cmd 'echo $"HOME"' "COMPLEX"
test_cmd 'echo $"HOME"$USER' "COMPLEX"
test_cmd '>> $HOME' "COMPLEX"
test_cmd '>> "$HOME"' "COMPLEX"
test_cmd 'cat <missing' "COMPLEX"
test_cmd 'cat >invalid_perm' "COMPLEX"

echo "" >&2
echo "=== RESULTS ===" >&2
if [ -s "$OUTPUT_FILE" ]; then
    echo "Segfaults gefunden in:" >&2
    cat "$OUTPUT_FILE"
    echo "" >&2
    echo "Total: $(wc -l < "$OUTPUT_FILE") commands" >&2
else
    echo "Keine Segfaults gefunden! ✓" >&2
fi

rm -f /tmp/minishell_test_output.txt
