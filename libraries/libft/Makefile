# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 16:17:10 by mgunter           #+#    #+#              #
#    Updated: 2025/06/14 16:17:13 by mgunter          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler und Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes

# Name der Bibliothek
NAME = libft.a

# Ordner
SRCDIR = sources
OBJDIR = objects
INCDIR = includes

# Alle .c Dateien im sources-Ordner finden
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Objektdateien im objects-Ordner mit .o Endung
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Default Ziel
all: $(NAME)

# Archiv erstellen aus Objektdateien
$(NAME): $(OBJ)
	ar rcs $@ $^
	@echo "Archive created: $(NAME)"

# Regel: .c zu .o kompilieren, objects-Ordner vorher anlegen
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

# Erstelle objects-Ordner, falls nicht vorhanden
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean löscht objects-Ordner komplett
clean:
	@rm -rf $(OBJDIR)
	@echo "Removed objects directory"

# Fclean löscht objects + Archiv
fclean: clean
	@rm -f $(NAME)
	@echo "Removed archive $(NAME)"

# Rebuild
re: fclean all
	@echo "Rebuild done"

# Phony Targets
.PHONY: all clean fclean re

