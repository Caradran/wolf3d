NAME = libvec2.a
SRC = libvec2.c libvec2_1.c
SRC_PATH = srcs
OBJ_PATH = objs
OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)
FLAGS = -Werror -Wextra -Wall -Iinclude

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