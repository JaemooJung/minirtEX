NAME 		=	so_long

CC 			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

FILES 		=	main.c \

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