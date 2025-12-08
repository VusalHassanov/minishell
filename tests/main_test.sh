#!/bin/bash

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RED='\033[0;31m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

PATH_MINISHELL="/home/martin/Desktop/Minishell-Group"
PATH_TEST_BUILTIN="/home/martin/Desktop/Minishell-Group/tests"
# PATH_TEST_EXTERN
# PATH_TEST_PARSING

printf "========================================================"
printf "====================MINISHELL TESTER===================="
printf "========================================================"

printf "Change Directory..."
cd "$PATH_MINISHELL"
printf "New Directory: $(pwd)"
printf "Build Minishell..."
if make > /dev/null 2>&1; then
    echo "✅ Build successful"
else
    echo "❌ Build failed! Here's what went wrong:"
    make
    exit 1
fi

printf "==================Check Single Commands================="
printf "==========================echo=========================="

# -t entfernt newline am Ende der Zeile
readarray -t commands < $PATH_TEST_BUILTIN/test_builtin.txt

# @ Symbol separiert jedes Arrayelement als einzelnen String. 
# Mit * werden alle Elemente zu EINEM String zusammengefasst
for cmd in "${commands[@]}"; do
    printf "${YELLOW}Testing: $cmd\n${NC}"
    printf "%s\nexit\n" "$cmd" | ./minishell
done


exit