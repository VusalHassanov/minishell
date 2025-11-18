# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 00:00:00 by vhasanov          #+#    #+#              #
#    Updated: 2025/11/14 22:52:53 by vhasanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RL_FLAG = -lreadline

# Directories (relative to tests folder)
PARENT_DIR = ..
SRC_DIR = $(PARENT_DIR)/sources
INC_DIR = $(PARENT_DIR)/includes
LIBFT_DIR = $(PARENT_DIR)/libraries/libft
OBJ_DIR = objects
OUT_DIR = running_test

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files - ONLY ESSENTIALS
LEXING_SRC = $(wildcard $(SRC_DIR)/lexing/*.c)
BUILTIN_SRC = $(wildcard $(SRC_DIR)/built-in/*.c) \
              $(wildcard $(SRC_DIR)/built-in/built-in_helpers/*.c) \
              $(wildcard $(SRC_DIR)/built-in/built-in_helpers/env_helper/*.c)
SIGNALS_SRC = $(wildcard $(SRC_DIR)/signals/*.c)

# All sources - removed parser, expansion, pipes, etc.
ALL_SRC = $(LEXING_SRC) $(BUILTIN_SRC) $(SIGNALS_SRC)

# Object files
ALL_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ALL_SRC))

# Test executable
TEST_NAME = $(OUT_DIR)/test_minishell

# Build libft
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Create directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes -c $< -o $@

# Main test target
all: $(TEST_NAME)

# Build test executable with main.c
$(TEST_NAME): $(ALL_OBJ) $(LIBFT) | $(OUT_DIR)
	@echo "Linking test executable..."
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes \
		main.c $(ALL_OBJ) $(LIBFT) $(RL_FLAG) -o $(TEST_NAME)
	@echo "✓ Test executable created: $(TEST_NAME)"

# Run the test
run: $(TEST_NAME)
	@echo "Running test..."
	@./$(TEST_NAME)

# Clean object files
clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	@echo "Removing test executable..."
	@rm -rf $(OUT_DIR)

# Rebuild
re: fclean all

.PHONY: all run clean fclean re