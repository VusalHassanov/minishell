# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: martin <martin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/25 23:45:20 by vhasanov          #+#    #+#              #
#    Updated: 2025/10/28 13:45:58 by martin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiling
NAME = minishell
CC = cc
# CC_FLAGS = -Wall -Wextra -Werror
CC_FLAGS = 
RL_FLAG = -lreadline

# Libft
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Modules
LEXING_SRC = $(wildcard sources/lexing/*.c)
PARSER_SRC = $(wildcard sources/parser/*.c)
EXPAND_SRC = # add later
BUILTIN_SRC = $(wildcard sources/built-in/*c)
PIPES_SRC = # add later
REDIRECT_SRC = # add later
MAIN_SRC = # add later

# Main Build
SRC_DIR = sources
INC_DIR	= includes
OBJ_DIR = objects

SRC = $(MAIN_SRC) $(LEXING_SRC) $(PARSER_SRC) $(BUILTIN_SRC) $(PIPES_SRC)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Test Builds (without main minishell program!)
TEST_PATH = tests/running_test

TEST_PARSER_SRC = $(LEXING_SRC) $(PARSER_SRC)
TEST_PARSER_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_PARSER_SRC))

TEST_BUILTIN_SRC = $(BUILTIN_SRC)
TEST_BUILTIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_BUILTIN_SRC))

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

# Main target
all: $(NAME)

# Build main executable
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) $(RL_FLAG) -o $(NAME)

# Include rule to put executable into tests/running_tests
test_parser: $(TEST_PARSER_OBJ) $(LIBFT)
	@mkdir -p $(TEST_PATH)
	$(CC) $(CC_FLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes tests/test_lexing/test_parsing.c $(RL_FLAG) $(TEST_PARSER_OBJ) $(LIBFT) -o $(TEST_PATH)/$@

test_builtin: $(TEST_)
	@mkdir -p $(TEST_PATH)
	$(CC) $(CC_FLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes tests/test_builtin/test_built-in.c $(RL_FLAG) $(TEST_PARSER_OBJ) $(LIBFT) -o $(TEST_PATH)/$@

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
