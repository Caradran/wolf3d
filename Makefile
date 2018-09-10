NAME = wolf3d
LIB_PATH = libvec2 libmath
MAKE_LIB = $(LIB_PATH:%=make -C %;)
CLEAN_LIB = $(LIB_PATH:%=make clean -C %;)
FCLEAN_LIB = $(LIB_PATH:%=make fclean -C %;)
SRC = Wolf3D.c
SRC_PATH = srcs
OBJ_PATH = objs
OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)
LIB_FLAGS = $(LIB_PATH:%=-L%)
INC_FLAGS = $(LIB_PATH:%=-I%/include) -Iinclude
FLAGS = $(INC_FLAGS) 

all : $(LIB_PATH) $(NAME)

$(NAME) : libs $(OBJ)
	$(CC) -o $(NAME) $(FLAGS) $(LIB_FLAGS) $(OBJ)

libs :
	$(MAKE_LIB)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(CLEAN_LIB)
	rm -f $(OBJ);

fclean :
	$(FCLEAN_LIB)
	rm -f $(OBJ);
	rm -f $(NAME);

re : fclean all

.PHONY : clean fclean all re libs