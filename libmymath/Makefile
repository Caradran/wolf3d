# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esuits <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/07 18:29:41 by esuits            #+#    #+#              #
#    Updated: 2018/10/07 18:29:42 by esuits           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmymath.a
SRC = libmymath.c libmymath2.c
SRC_PATH = srcs
OBJ_PATH = objs
OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)
FLAGS = -Werror -Wextra -Wall -Iinclude -O3

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ);
	ranlib $(NAME);

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ);

fclean : clean
	rm -f $(NAME);

re : fclean all

.PHONY : clean fclean all re
