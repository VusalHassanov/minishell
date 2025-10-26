# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_parsing.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/19 14:45:02 by mgunter           #+#    #+#              #
#    Updated: 2025/10/20 16:37:33 by mgunter          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RED='\033[0;31m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

FILE="./tests/test_exec/test_parser"

# Counter for passed/failed tests
PASSED=0
FAILED=0
TOTAL=0

# Helper function to run a test
run_test() {
    local test_num=$1
    local test_name=$2
    local input=$3
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${BLUE}========================================${NC}"
    echo -e "${GREEN}Test $test_num: $test_name${NC}"
    echo -e "${CYAN}Input: ${NC}$input"
    echo ""
    
    # Run your parser
    echo -e "${YELLOW}Your Parser Output:${NC}"
    printf '%s\n' "$input" | $FILE
    
    echo ""
    echo -e "${MAGENTA}Bash Shell Interpretation:${NC}"
    # Show how bash would interpret it (using eval with echo to show tokens)
    eval "set -- $input; for arg in \"\$@\"; do echo \"Token: [\$arg]\"; done"
    
    echo -e "${BLUE}========================================${NC}\n"
}

echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║     TOKENIZER COMPARISON TEST SUITE    ║${NC}"
echo -e "${BLUE}║   Your Parser vs. Bash Shell Behavior  ║${NC}"
echo -e "${BLUE}╔════════════════════════════════════════╗${NC}\n"

# Test 1: Simple arguments with quotes
run_test 1 "Simple arguments with quotes" '"hello world" whats cooking'

# Test 2: Single word
run_test 2 "Single word" 'blablabla'

# Test 3: Double quotes with spaces
run_test 3 "Double quotes with spaces" '"hello world"'

# Test 4: Single quotes with spaces
run_test 4 "Single quotes with spaces" "'hello world'"

# Test 5: Empty quotes
run_test 5 "Empty double quotes" 'hello "" world'

# Test 6: Multiple arguments with quotes
run_test 6 "Multiple arguments with quotes" 'arg1 "arg 2" arg3'

# Test 7: Shell operators - Pipe
run_test 7 "Pipe operator" 'echo hello |'

# Test 8: Redirect operators
run_test 8 "Redirect operators" 'cat < input.txt > output.txt'

# Test 9: Double redirect (append)
run_test 9 "Double redirect (append)" 'echo >> file.txt'

# Test 10: Heredoc
run_test 10 "Heredoc operator" 'cat << EOF'

# Test 11: Logical AND
run_test 11 "AND operator" 'cmd1 && cmd2'

# Test 12: Quotes with special characters
run_test 12 "Quotes with special characters" '"hello|world>test"'

# Test 13: Mixed quotes - double inside single
run_test 13 "Double quote inside single quotes" ''"'"'he said "hi"'"'"''

# Test 14: Adjacent quotes (no space)
run_test 14 "Adjacent quotes" '"hello"'"'"'world'"'"''

# Test 15: Multiple spaces
run_test 15 "Multiple spaces between args" 'arg1    arg2     arg3'

# Test 16: Quote at the end
run_test 16 "Quote at the end" 'hello "world"'

# Test 17: Single quote inside double quotes
run_test 17 "Single quote inside double quotes" '"what'"'"'s going on"'

# Test 18: Empty string
run_test 18 "Empty string" '""'

# Test 19: Multiple empty strings
run_test 19 "Multiple empty strings" '"" "" ""'

# Test 20: Complex mixed quotes
run_test 20 "Complex mixed quotes" '"hello"world"test"'

echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║          ALL TESTS COMPLETED           ║${NC}"
echo -e "${BLUE}║   Total Tests: ${TOTAL}                       ║${NC}"
echo -e "${BLUE}╔════════════════════════════════════════╗${NC}\n"

echo -e "${YELLOW}Note: Compare outputs manually to see differences${NC}"
echo -e "${YELLOW}Your parser should match Bash's token behavior${NC}"

# Test 3: Quotes with single quote inside double quotes
echo -e "${GREEN}Test 3: Single quote inside double quotes${NC}"
echo -e "${YELLOW}Expected: 2 tokens -> [whats' going] [on]${NC}"
printf '%s\n' "\"whats' \"going on\"\"" | $FILE
echo ""

# Test 4: Double quotes with spaces
echo -e "${GREEN}Test 4: Double quotes with spaces${NC}"
echo -e "${YELLOW}Expected: 1 token -> [hello world]${NC}"
printf '%s\n' '"hello world"' | $FILE
echo ""

# Test 5: Single quotes with spaces
echo -e "${GREEN}Test 5: Single quotes with spaces${NC}"
echo -e "${YELLOW}Expected: 1 token -> [hello world]${NC}"
printf '%s\n' "'hello world'" | $FILE
echo ""

# Test 6: Mixed quotes
echo -e "${GREEN}Test 6: Mixed quotes${NC}"
echo -e "${YELLOW}Expected: 1 token -> [hello \"world\"]${NC}"
printf '%s\n' ''"'"'hello "world"'"'"'' | $FILE
echo ""

# Test 7: Empty quotes
echo -e "${GREEN}Test 7: Empty double quotes${NC}"
echo -e "${YELLOW}Expected: 3 tokens -> [hello] [] [world]${NC}"
printf '%s\n' 'hello "" world' | $FILE
echo ""

# Test 8: Multiple arguments with quotes
echo -e "${GREEN}Test 8: Multiple arguments with quotes${NC}"
echo -e "${YELLOW}Expected: 3 tokens -> [arg1] [arg 2] [arg3]${NC}"
printf '%s\n' 'arg1 "arg 2" arg3' | $FILE
echo ""

# Test 9: Shell operators
echo -e "${GREEN}Test 9: Pipe operator${NC}"
echo -e "${YELLOW}Expected: 3 tokens -> [echo] [hello] [|]${NC}"
printf '%s\n' 'echo hello |' | $FILE
echo ""

# Test 10: Redirect operators
echo -e "${GREEN}Test 10: Redirect operators${NC}"
echo -e "${YELLOW}Expected: 5 tokens -> [cat] [<] [input.txt] [>] [output.txt]${NC}"
printf '%s\n' 'cat < input.txt > output.txt' | $FILE
echo ""

# Test 11: Double redirect
echo -e "${GREEN}Test 11: Double redirect (append)${NC}"
echo -e "${YELLOW}Expected: 3 tokens -> [echo] [>>] [file.txt]${NC}"
printf '%s\n' 'echo >> file.txt' | $FILE
echo ""

# Test 12: Heredoc
echo -e "${GREEN}Test 12: Heredoc operator${NC}"
echo -e "${YELLOW}Expected: 3 tokens -> [cat] [<<] [EOF]${NC}"
printf '%s\n' 'cat << EOF' | $FILE
echo ""

# Test 13: Logical operators
echo -e "${GREEN}Test 13: AND operator${NC}"
echo -e "${YELLOW}Expected: 3 tokens -> [cmd1] [&&] [cmd2]${NC}"
printf '%s\n' 'cmd1 && cmd2' | $FILE
echo ""

# Test 14: Complex command with multiple operators
echo -e "${GREEN}Test 14: Complex command${NC}"
echo -e "${YELLOW}Expected: 9 tokens -> [echo] [hello] [>] [out.txt] [&&] [cat] [out.txt] [|] [grep] [hello]${NC}"
printf '%s\n' 'echo hello > out.txt && cat out.txt | grep hello' | $FILE
echo ""

# Test 15: Quotes with special characters
echo -e "${GREEN}Test 15: Quotes with special characters${NC}"
echo -e "${YELLOW}Expected: 1 token -> [hello|world>test]${NC}"
printf '%s\n' '"hello|world>test"' | $FILE
echo ""

# Test 16: Single quote with double quote inside
echo -e "${GREEN}Test 16: Double quote inside single quotes${NC}"
echo -e "${YELLOW}Expected: 1 token -> [he said \"hi\"]${NC}"
printf '%s\n' ''"'"'he said "hi"'"'"'' | $FILE
echo ""

# Test 17: Adjacent quotes
echo -e "${GREEN}Test 17: Adjacent quotes (no space)${NC}"
echo -e "${YELLOW}Expected: 1 token -> [helloworld]${NC}"
printf '%s\n' '"hello"'"'"'world'"'"'' | $FILE
echo ""

# Test 18: Multiple spaces
echo -e "${GREEN}Test 18: Multiple spaces between args${NC}"
echo -e "${YELLOW}Expected: 3 tokens -> [arg1] [arg2] [arg3]${NC}"
printf '%s\n' 'arg1    arg2     arg3' | $FILE
echo ""

# Test 19: Tabs and spaces
echo -e "${GREEN}Test 19: Tabs and spaces${NC}"
echo -e "${YELLOW}Expected: 2 tokens -> [hello] [world]${NC}"
printf 'hello\tworld\n' | $FILE
echo ""

# Test 20: Quote at the end
echo -e "${GREEN}Test 20: Quote at the end${NC}"
echo -e "${YELLOW}Expected: 2 tokens -> [hello] [world]${NC}"
printf '%s\n' 'hello "world"' | $FILE
echo ""

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}       ALL TESTS COMPLETED${NC}"
echo -e "${BLUE}========================================${NC}"
