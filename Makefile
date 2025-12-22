# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/25 23:45:20 by vhasanov          #+#    #+#              #
#    Updated: 2025/12/22 12:18:44 by mgunter          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiling
NAME = minishell
# CC = cc
CC_FLAGS = -Wall -Wextra -Werror -g -O0
CC_FLAGS = 
RL_FLAG = -lreadline

# Libft
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Modules
LEXING_SRC = sources/lexing/tokens.c \
             sources/lexing/tokens_checker.c \
             sources/lexing/tokens_checker2.c \
             sources/lexing/tokens_utils.c \
             sources/lexing/tokens_utils2.c

PARSER_SRC = sources/parser/ast.c \
             sources/parser/ast_utils.c \
             sources/parser/parser.c \
             sources/parser/parser_utils.c

EXPAND_SRC = sources/expansion/env_var_expansion.c \
             sources/expansion/expand_exit.c \
             sources/expansion/expander.c \
             sources/expansion/quotes.c \
             sources/expansion/str_replace_helper.c

BUILTIN_SRC = sources/built-in/cd.c \
              sources/built-in/echo.c \
              sources/built-in/env.c \
              sources/built-in/exit.c \
              sources/built-in/export.c \
              sources/built-in/pwd.c \
              sources/built-in/unset.c \
              sources/built-in/built-in_helpers/cd_helper.c \
              sources/built-in/built-in_helpers/echo_helper.c \
              sources/built-in/built-in_helpers/exit_helper.c \
              sources/built-in/built-in_helpers/export_helper.c \
              sources/built-in/built-in_helpers/helper.c \
              sources/built-in/built-in_helpers/env_helper/env_helper.c \
              sources/built-in/built-in_helpers/env_helper/env_helper2.c

SIGNALS_SRC = sources/signals/signals.c \
              sources/signals/signals_setup.c

EXEC_SRC = sources/execution/execution.c \
           sources/execution/execution_helper.c \
           sources/execution/execution_helper2.c \
           sources/execution/external/external.c \
           sources/execution/external/search.c

PIPES_SRC = sources/pipes/pipes.c \
            sources/pipes/pipes_helper.c

REDIRECT_SRC = sources/redirections/heredoc.c \
               sources/redirections/heredoc_tempfile.c \
               sources/redirections/heredoc_utils.c \
               sources/redirections/redir_append.c \
               sources/redirections/redir_in.c \
               sources/redirections/redir_out.c

MAIN_SRC = sources/main.c

# Main Build
SRC_DIR = sources
INC_DIR	= includes
OBJ_DIR = objects

SRC = $(MAIN_SRC) $(LEXING_SRC) $(PARSER_SRC) $(BUILTIN_SRC) $(SIGNALS_SRC) $(PIPES_SRC) $(EXEC_SRC) $(REDIRECT_SRC) $(EXPAND_SRC)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: $(NAME)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule for compiling .c to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes -c $< -o $@

# Build main executable
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) $(RL_FLAG) -o $(NAME)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean everything
fclean: clean
	rm -f $(NAME)
	rm -rf tests/running_test/test_parser
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re test_parser test_builtin
