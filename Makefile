NAME		=	cub3d
INC			=	./includes/
LIBS		=	./libs/
BIN			=	./.bin/
SRC			=	./src/
SRCS		=	main.c

OBJS		=	$(addprefix $(BIN), $(SRCS:.c=.o))
MLX			=	$(LIBS)mlx/libmlx.a
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3

all			:	$(NAME)

$(BIN)%.o	:	$(SRC)%.c
				@ mkdir -p $(dir $@)
				@ $(CC) $(CFLAGS) -c -o $@ $^ -I$(INC) -I$(LIBS)

%.a			:
				@ make -sC $(dir $@)

$(NAME)		:	$(MLX) $(OBJS)
				@ $(CC) $(CFLAGS) -o $@ $^ -L$(dir $(MLX)) -lmlx -framework \
					OpenGL -framework AppKit

clean		:
				@ rm -rfv $(BIN)
				@ make -sC $(dir $(MLX)) clean

fclean		:	clean
				@ rm -fv $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
