#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    interactive_test.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: martin <martin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/25 16:10:00 by martin            #+#    #+#              #
#    Updated: 2025/11/25 16:10:00 by martin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Farben
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

# Array mit allen Test-Befehlen
commands=(
    "echo bonjour ; |"
    "echo bonjour | |"
    "|"
    "echo bonjour |;"
    "echo bonjour ; ls"
    "echo bonjour > test\ 1"
    "cd \$HOME/Documents"
    "echo \"\\s\" & echo \"\\s\""
    "echo >"
    "echo -n -n -nnnn -nnnnm"
    "cat /dev/random | head -n 1 | cat -e"
    "unset var1 # with undefined var1"
    "export \"\" et unset \"\""
    "echo test > file test1"
    "\$"
    "not_cmd bonjour > salut"
    "env puis export puis env # vars aren't sorted"
    "cat Makefile | grep pr | head -n 5 | cd test (mybin) # check status code"
    "cat Makefile | grep pr | head -n 5 | cat test (bin) # check status code"
    "cat Makefile | grep pr | head -n 5 | hello (NA) # check status code"
    "echo bonjour >>> test"
    "echo bonjour > > out"
    "echo 2 >> out1 > out2"
    "echo 2 > out1 >> out2"
    "cat < test # with non-existent test"
    "export var; export var=test"
    "echo bonjour > \$test # with test not defined"
    "file_name_in_current_dir"
    "cd ../../../../../.. ; pwd"
    "ctrl-C . 130 sur bin(ex : sleep 10)&line vide"
    "ctrl-\\ .131 sur bin"
    "echo \"bip | bip ; coyotte > < \" \""
    "cat | cat | cat | ls # check outputs order"
    "\$bla # with bla not defined"
    "export var =\"cat Makefile | grep >\""
    "export \"test=ici\"=coucou"
    "c\$var Makefile # with var=at"
    "\$LESS\$VAR"
    "/bin/echo bonjour"
    "not_cmd"
    "sleep 5 | exit"
    "echo bonjour > \$test w/ t"
    "\"exit retour a la ligne\""
    "minishell # binary not in path without \"./\" before"
    "cat diufosgid # check exit code"
    "exit # should return the last exit code value"
    "exit -10"
    "exit +10"
    ";"
    "echo coucou | ;"
    "echo \"\$HOME\""
    "echo '\$HOME'"
    "export ; env # display is different for both commands"
    "echo \$HOME"
    "> log echo coucou"
    "echo hudifg d | | hugdfihd"
    "echo"
    "echo simple"
    "echo -n simple"
    "echo ''"
    "echo \"\""
    "echo \"\\\""
    "echo \"\\n \\n \\n\""
    "echo \"\\n \\n \\\\n\""
    "echo ;;"
    "echo hi\";\" hihi"
    "echo hi \" ; \" hihi"
    "cd"
    "cd ."
    "cd ~"
    "cd /"
    "cd no_file"
    "cd a b c d"
    "pwd a"
    "pwd a b c d"
    "export LOL=lala ROR=rara"
    "unset LOL ROR"
    "export \"HI= hi\""
    "export \"HI =hi\""
    "/bin/ls"
    "echo \$?"
    "l^Ds"
    "echo |"
    "| echo"
    "sort | ls # check output order"
    "cat < >"
    "cat < <"
    "cat > >"
    "> a ls > b < Makefile"
    "echo > a Hello World!"
    "> a echo Hello World!"
    "cat < Makefile | grep gcc > output"
    "exit 0 | exit 1"
    "exit 1 | exit 0"
)

# Funktion für interaktive Tests
run_interactive_test() {
    local current=1
    local total=${#commands[@]}
    
    echo -e "${GREEN}╔══════════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║              Interactive Minishell Test                  ║${NC}"
    echo -e "${GREEN}║          Press ENTER to run next command                 ║${NC}"
    echo -e "${GREEN}║          Press 'q' + ENTER to quit                       ║${NC}"
    echo -e "${GREEN}╚══════════════════════════════════════════════════════════╝${NC}"
    echo
    
    if [ ! -f "./minishell" ]; then
        echo -e "${RED}Error: ./minishell not found. Run 'make' first.${NC}"
        exit 1
    fi
    
    for cmd in "${commands[@]}"; do
        echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
        echo -e "${CYAN}Test $current/$total${NC}"
        echo -e "${YELLOW}Command: ${NC}$cmd"
        echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
        
        # Warte auf User Input
        echo -e "${GREEN}Press ENTER to run this command (or 'q' to quit): ${NC}"
        read -r user_input
        
        # Prüfe ob User beenden möchte
        if [[ "$user_input" == "q" || "$user_input" == "quit" ]]; then
            echo -e "${YELLOW}Test abgebrochen auf Benutzerwunsch.${NC}"
            break
        fi
        
        # Führe den Befehl aus
        echo -e "${CYAN}Executing command...${NC}"
        echo
        
        # Erstelle temporäre Datei mit dem Befehl
        echo "$cmd" > /tmp/current_test.txt
        echo "exit" >> /tmp/current_test.txt
        
        # Führe minishell mit dem Befehl aus
        if [[ "$cmd" == *"valgrind"* ]]; then
            # Für Valgrind tests
            valgrind ./minishell < /tmp/current_test.txt
        else
            # Normale Befehle
            ./minishell < /tmp/current_test.txt
        fi
        
        echo
        echo -e "${YELLOW}Command completed. Exit code: $?${NC}"
        
        # Cleanup
        rm -f /tmp/current_test.txt
        
        ((current++))
        echo
    done
    
    echo -e "${GREEN}Interactive test completed!${NC}"
}

# Funktion für Batch-Modus (wie ursprünglich)
run_batch_test() {
    echo -e "${BLUE}Running all tests in batch mode...${NC}"
    
    cat > commands.txt << 'EOF'
    echo bonjour ; |
    echo bonjour | |
    |
    echo bonjour |;
    echo bonjour ; ls
    echo bonjour > test\ 1
    cd $HOME/Documents
    echo "\s" & echo "\s"
    echo >
    echo -n -n -nnnn -nnnnm
    cat /dev/random | head -n 1 | cat -e
    unset var1 # with undefined var1
    export "" et unset ""
    echo test > file test1
    $
    not_cmd bonjour > salut
    env puis export puis env # vars aren't sorted
    cat Makefile | grep pr | head -n 5 | cd test (mybin) # check status code
    cat Makefile | grep pr | head -n 5 | cat test (bin) # check status code
    cat Makefile | grep pr | head -n 5 | hello (NA) # check status code
    echo bonjour >>> test
    echo bonjour > > out
    echo 2 >> out1 > out2
    echo 2 > out1 >> out2
    cat < test # with non-existent test
    export var; export var=test
    echo bonjour > $test # with test not defined
    file_name_in_current_dir
    cd ../../../../../.. ; pwd
    ctrl-C . 130 sur bin(ex : sleep 10)&line vide
    ctrl-\ .131 sur bin
    echo "bip | bip ; coyotte > < " "
    cat | cat | cat | ls # check outputs order
    $bla # with bla not defined
    export var ="cat Makefile | grep >"
    export "test=ici"=coucou
    c$var Makefile # with var=at
    $LESS$VAR
    /bin/echo bonjour
    not_cmd
    sleep 5 | exit
    echo bonjour > $test w/ t
    "exit retour a la ligne"
    minishell # binary not in path without "./" before
    cat diufosgid # check exit code
    exit # should return the last exit code value
    exit -10
    exit +10
    ;
    echo coucou | ;
    echo "$HOME"
    echo '$HOME'
    export ; env # display is different for both commands
    echo $HOME
    > log echo coucou
    echo hudifg d | | hugdfihd
    echo
    echo simple
    echo -n simple
    echo ''
    echo ""
    echo "\"
    echo "\n \n \n"
    echo "\n \n \\n"
    echo ;;
    echo hi";" hihi
    echo hi " ; " hihi
    cd
    cd .
    cd ~
    cd /
    cd no_file
    cd a b c d
    pwd a
    pwd a b c d
    export LOL=lala ROR=rara
    unset LOL ROR
    export "HI= hi"
    export "HI =hi"
    /bin/ls
    # write something the press ctrl+c
    # write something then press ctrl+d
    # write something then press ctrl+\
    echo $?
    l^Ds
    echo |
    | echo
    sort | ls # check output order
    cat < >
    cat < <
    cat > >
    > a ls > b < Makefile
    echo > a Hello World!
    > a echo Hello World!
    cat < Makefile | grep gcc > output
    exit 0 | exit 1
    exit 1 | exit 0
EOF

    valgrind ./minishell < commands.txt
    rm commands.txt
}

# Hauptmenü
main() {
    echo -e "${BLUE}Wähle Test-Modus:${NC}"
    echo -e "1) ${GREEN}Interactive${NC} - Schritt für Schritt mit Enter"
    echo -e "2) ${YELLOW}Batch${NC} - Alle Tests auf einmal (wie ursprünglich)"
    echo -e "3) ${RED}Quit${NC}"
    echo
    echo -e "${CYAN}Deine Wahl (1/2/3): ${NC}"
    read -r choice
    
    case $choice in
        1)
            run_interactive_test
            ;;
        2)
            run_batch_test
            ;;
        3)
            echo -e "${YELLOW}Auf Wiedersehen!${NC}"
            exit 0
            ;;
        *)
            echo -e "${RED}Ungültige Wahl. Verwende 1, 2 oder 3.${NC}"
            main
            ;;
    esac
}

# Script starten
main "$@"