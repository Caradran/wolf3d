NAME = wolf3d
LIB_PATH = libvec2 libmymath libgraph libft
MAKE_LIB = $(LIB_PATH:%=make -C %;)
CLEAN_LIB = $(LIB_PATH:%=make clean -C %;)
FCLEAN_LIB = $(LIB_PATH:%=make fclean -C %;)
SRC = testsdl.c draw.c save_map.c wolf3d.c get_next_line.c textures.c
SRC_PATH = srcs
OBJ_PATH = objs
OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)
LIB_FLAGS = $(LIB_PATH:%=-L%) -lmymath -lvec2 -lft -lgraph `sdl2-config --libs` -lSDL2_image
INC_FLAGS = $(LIB_PATH:%=-I%/include) -Iinclude `sdl2-config --cflags`
FLAGS = $(INC_FLAGS) -g3

all : $(NAME)

$(NAME) : libs $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(LIB_FLAGS) -o $(NAME)

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