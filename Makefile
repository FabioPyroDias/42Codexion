# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/16 18:46:36 by fda-cruz          #+#    #+#              #
#    Updated: 2026/05/16 20:58:53 by fda-cruz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

INCLUDE = -Iinclude

SRC_DIR = src
PARSER_DIR = src/parser
UTILS_DIR = src/utils

MAIN_FILE = codexion.c
PARSER_FILES = parser.c parser_aux.c
UTILS_FILES = utils.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(MAIN_FILE:.c=.o))
OBJ += $(addprefix $(OBJ_DIR)/,$(PARSER_FILES:.c=.o))
OBJ += $(addprefix $(OBJ_DIR)/,$(UTILS_FILES:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(PARSER_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) codexion

re: fclean all
