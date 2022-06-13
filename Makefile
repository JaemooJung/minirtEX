NAME 		=	miniRT

CC 			=	gcc
CFLAGS		=	
RM			=	rm -f

FILES 		=	main.c \
				error.c \
				ray.c \
				scene.c \
				draw.c \
				utils.c \
				utils_vec_operations.c \
				utils_vec_operations_2.c \
				utils_vec_operations_3.c \
				mlx_utils.c \
				objects.c \

SRC_DIR		=	./sources/
INC_DIR		=	./includes

SRCS		=	$(addprefix $(SRC_DIR), $(FILES))

OBJS		=	$(SRCS:.c=.o)

MLX			=	libmlx.dylib

.PHONY: all clean fclean re

all: $(MLX) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I./minilibx -I$(INC_DIR) -c -o $@ $<

$(MLX):
	make all -C minilibx/

$(NAME): $(OBJS)
	$(CC) -L ./minilibx -lmlx -framework OpenGL -framework AppKit -o $@ $^
	install_name_tool -change libmlx.dylib ./minilibx/libmlx.dylib $(NAME)
clean:
	$(RM) $(OBJS)
	make clean -C minilibx

fclean: clean
	$(RM) $(NAME)
	make clean -C minilibx
	
re: clean all