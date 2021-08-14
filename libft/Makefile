# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/20 21:28:19 by ligeorgi          #+#    #+#              #
#    Updated: 2020/05/20 21:30:50 by ligeorgi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror

include libft.mk

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT_OBJECTS_DIRECTORY) $(LIBFT_OBJECTS)
	@ar rc $(NAME) $(LIBFT_OBJECTS)
	@ranlib $(NAME)
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(LIBFT_OBJECTS_DIRECTORY):
	@mkdir -p $(LIBFT_OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(LIBFT_OBJECTS_DIRECTORY) was created$(RESET)"

$(LIBFT_OBJECTS_DIRECTORY)%.o : $(LIBFT_SOURCES_DIRECTORY)%.c $(LIBFT_HEADERS)
	@$(CC) $(FLAGS) -c -I$(LIBFT_HEADERS_DIRECTORY) $< -o $@

clean:
	@rm -rf $(LIBFT_OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(LIBFT_OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
