# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/16 18:46:36 by fda-cruz          #+#    #+#              #
#    Updated: 2026/06/07 14:41:23 by fda-cruz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

INCLUDE = -Iinclude

SRC_DIR = src
PARSER_DIR = src/parser
SIMULATION_DIR = src/simulation
THREADS_DIR = src/threads
HEAP_DIR = src/heap

MAIN_FILE = codexion.c
PARSER_FILES = parser.c parser_utils.c
SIMULATION_FILES =	simulation.c simulation_utils.c \
					simulation_utils2.c simulation_frees.c \
					simulation_threads.c
THREADS_FILES = coder.c coder_utils.c monitor.c monitor_utils.c
HEAP_FILE = heap.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(MAIN_FILE:.c=.o))
OBJ += $(addprefix $(OBJ_DIR)/,$(PARSER_FILES:.c=.o))
OBJ += $(addprefix $(OBJ_DIR)/,$(SIMULATION_FILES:.c=.o))
OBJ += $(addprefix $(OBJ_DIR)/,$(THREADS_FILES:.c=.o))
OBJ += $(addprefix $(OBJ_DIR)/,$(HEAP_FILE:.c=.o))

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

$(OBJ_DIR)/%.o : $(SIMULATION_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(THREADS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(HEAP_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) codexion

re: fclean all
