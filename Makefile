# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/10 09:12:01 by ligeorgi          #+#    #+#              #
#    Updated: 2020/12/10 09:12:15 by ligeorgi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc
FLAGS = -Wall -Werror -Wextra -o3
LIBRARIES = -lft -L$(LIBFT_DIRECTORY)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS_DIR)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS_DIR = $(LIBFT_DIRECTORY)includes/

HEADERS_LIST = lem_in.h\

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = main.c\
	get_line.c\
	get_ants.c\
	get_rooms.c\
	get_links.c\
	sort_rooms_by_names.c\
	set_graph.c\
	move_ants_and_print_results.c\
	move_ants_utils.c\
	free_data.c\
	utils.c\
	print.c\
	vertex_queue_init.c\
	vertex_queue_change.c\
	graph_iter.c\
	graph_utils.c\
	scan_head_queue_edges.c\
	reset_paths.c\
	reverse_new_path.c\

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

include $(LIBFT_DIRECTORY)libft.mk

LIBFT_1 = $(subst ./, , $(LIBFT_HEADERS))
LIBFT_1 += $(subst ./, , $(LIBFT_SOURCES))
LIBFT_2 = $(addprefix $(LIBFT_DIRECTORY), $(LIBFT_1))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS) $(LIBFT)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT): $(LIBFT_2)
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
