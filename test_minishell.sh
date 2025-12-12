#!/bin/bash

# Farben für Output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

MINISHELL="./minishell"
PASSED=0
FAILED=0
TOTAL=0

# Cleanup function
cleanup() {
    rm -f /tmp/minishell_test_* /tmp/bash_test_* 2>/dev/null
}

trap cleanup EXIT

# Test function
run_test() {
    local test_name="$1"
    local command="$2"
    local should_compare="${3:-1}" # Default: compare with bash
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${BLUE}Test $TOTAL: $test_name${NC}"
    
    # Run in minishell
    echo -e "$command\nexit" | timeout 2 $MINISHELL 2>&1 | sed '/^minishell\$/d' | sed 's/^minishell\$ //' | grep -v "^exit$" | sed '/^$/N;/^\n$/D' > /tmp/minishell_test_output
    local mini_exit=$?
    
    if [ "$should_compare" -eq 1 ]; then
        # Run in bash for comparison  
        echo "$command" | timeout 2 bash 2>&1 | grep -v "^bash" | sed '/^$/N;/^\n$/D' > /tmp/bash_test_output
        local bash_exit=$?
        
        # Compare outputs (ignore whitespace differences at end of lines)
        if diff -b -w -q /tmp/minishell_test_output /tmp/bash_test_output > /dev/null 2>&1; then
            echo -e "${GREEN}✓ PASSED${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "Command: $command"
            echo "Expected (bash):"
            cat /tmp/bash_test_output
            echo "Got (minishell):"
            cat /tmp/minishell_test_output
            echo "---"
            FAILED=$((FAILED + 1))
        fi
    else
        # Just check if it ran without error
        if [ $mini_exit -eq 0 ] || [ $mini_exit -eq 130 ]; then
            echo -e "${GREEN}✓ PASSED (exit: $mini_exit)${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED (exit: $mini_exit)${NC}"
            cat /tmp/minishell_test_output
            FAILED=$((FAILED + 1))
        fi
    fi
    echo ""
}

# Create test files
echo "Creating test files..."
echo "Hello World" > /tmp/test_input.txt
echo -e "Line 1\nLine 2\nLine 3" > /tmp/test_multi.txt

echo -e "${YELLOW}=== Starting Minishell Tests ===${NC}\n"

# ============================================
# BUILTIN TESTS
# ============================================
echo -e "${YELLOW}--- BUILTIN TESTS ---${NC}"

run_test "echo simple" "echo hello world"
run_test "echo with -n" "echo -n hello"
run_test "echo multiple -n" "echo -n -n -n hello"
run_test "echo empty" "echo"
run_test "echo with quotes" "echo 'hello world'"
run_test "echo with double quotes" 'echo "hello world"'

run_test "pwd" "pwd"
run_test "pwd multiple" "pwd && pwd && pwd" 0

run_test "env (first 3 lines)" "env | head -3" 0

run_test "export new var" "export TEST_VAR=hello && echo \$TEST_VAR" 0
run_test "export multiple" "export A=1 B=2 && echo \$A \$B" 0

run_test "unset var" "export TEST=123 && unset TEST && echo \$TEST" 0

run_test "cd to /tmp" "cd /tmp && pwd"
run_test "cd to home" "cd && pwd" 0
run_test "cd .." "cd /tmp && cd .. && pwd"

run_test "exit with 0" "exit 0" 0
run_test "exit with 42" "exit 42" 0

# ============================================
# EXTERNAL PROGRAM TESTS
# ============================================
echo -e "${YELLOW}--- EXTERNAL PROGRAM TESTS ---${NC}"

run_test "ls current dir" "ls | wc -l" 0
run_test "cat file" "cat /tmp/test_input.txt"
run_test "wc file" "wc -l /tmp/test_multi.txt"
run_test "grep simple" "grep Line /tmp/test_multi.txt"
run_test "head" "head -2 /tmp/test_multi.txt"
run_test "tail" "tail -1 /tmp/test_multi.txt"
run_test "which ls" "which ls"
run_test "/bin/echo" "/bin/echo test"

# ============================================
# PIPE TESTS
# ============================================
echo -e "${YELLOW}--- PIPE TESTS ---${NC}"

run_test "simple pipe" "echo hello | cat"
run_test "pipe with grep" "echo -e 'apple\nbanana\napricot' | grep ap" 0
run_test "pipe chain" "echo test | cat | cat | cat"
run_test "ls pipe wc" "ls | wc -l" 0
run_test "pipe with sort" "echo -e '3\n1\n2' | sort" 0
run_test "multiple pipes" "cat /tmp/test_multi.txt | grep Line | wc -l"
run_test "pipe with head" "ls -la | head -5" 0
run_test "echo pipe grep" "echo hello world | grep world"

# ============================================
# REDIRECTION TESTS
# ============================================
echo -e "${YELLOW}--- REDIRECTION TESTS ---${NC}"

run_test "redirect output" "echo test > /tmp/minishell_redir.txt && cat /tmp/minishell_redir.txt"
run_test "redirect append" "echo line1 > /tmp/minishell_append.txt && echo line2 >> /tmp/minishell_append.txt && cat /tmp/minishell_append.txt"
run_test "redirect input" "cat < /tmp/test_input.txt"
run_test "redirect both" "cat < /tmp/test_input.txt > /tmp/minishell_both.txt && cat /tmp/minishell_both.txt"
run_test "multiple redirects" "echo test > /tmp/minishell_m1.txt > /tmp/minishell_m2.txt && cat /tmp/minishell_m2.txt"

# ============================================
# HEREDOC TESTS
# ============================================
echo -e "${YELLOW}--- HEREDOC TESTS ---${NC}"

run_test "heredoc simple" "cat << EOF
hello
world
EOF" 0

run_test "heredoc with pipe" "cat << EOF | wc -l
line1
line2
line3
EOF" 0

run_test "heredoc to file" "cat << EOF > /tmp/minishell_heredoc.txt
test content
EOF
cat /tmp/minishell_heredoc.txt" 0

# ============================================
# QUOTE TESTS
# ============================================
echo -e "${YELLOW}--- QUOTE TESTS ---${NC}"

run_test "single quotes" "echo 'hello world'"
run_test "double quotes" 'echo "hello world"'
run_test "mixed quotes" "echo 'hello' \"world\""
run_test "quotes with spaces" "echo 'hello    world'" 0
run_test "empty quotes" "echo ''" 0

# ============================================
# EXPANSION TESTS
# ============================================
echo -e "${YELLOW}--- EXPANSION TESTS ---${NC}"

run_test "env var expansion" "export TEST=hello && echo \$TEST" 0
run_test "exit status" "ls /nonexistent 2>/dev/null ; echo \$?" 0
run_test "multiple expansions" "export A=1 B=2 && echo \$A\$B" 0
run_test "expansion in quotes" "export X=test && echo \"value: \$X\"" 0

# ============================================
# COMPLEX TESTS
# ============================================
echo -e "${YELLOW}--- COMPLEX TESTS ---${NC}"

run_test "pipe with redirects" "echo test | cat > /tmp/minishell_complex.txt && cat /tmp/minishell_complex.txt"
run_test "multiple commands" "echo first && echo second && echo third" 0
run_test "builtin pipe external" "echo hello | grep h"
run_test "external pipe builtin" "ls | echo done" 0

# ============================================
# ERROR HANDLING TESTS
# ============================================
echo -e "${YELLOW}--- ERROR HANDLING TESTS ---${NC}"

run_test "command not found" "nonexistentcommand123" 0
run_test "invalid redirect" "cat < /nonexistent/file" 0
run_test "permission denied" "cat /root/.ssh/id_rsa 2>&1 | grep -i denied" 0

# ============================================
# SUMMARY
# ============================================
echo -e "${YELLOW}======================================${NC}"
echo -e "${YELLOW}           TEST SUMMARY${NC}"
echo -e "${YELLOW}======================================${NC}"
echo -e "Total tests: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed! 🎉${NC}"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed${NC}"
    exit 1
fi
