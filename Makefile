NAME		=	cub3d
INC			=	./includes/
LIBS		=	./libs/
BIN			=	./.bin/
SRC			=	./src/
SRCS		=	main.c \
				map_parser/gnl/get_next_line.c \
				map_parser/gnl/get_next_line_utils.c \
				map_parser/utils/ft_strlcpy.c \
				map_parser/utils/ft_strlen.c \
				map_parser/utils/freedom.c \
				map_parser/utils/ft_bzero.c \
				map_parser/utils/ft_split.c \
				map_parser/utils/ft_memset.c \
				map_parser/utils/ft_calloc.c \
				map_parser/utils/ft_strdup.c \
				map_parser/utils/ft_atoi.c \
				map_parser/map_parser.c

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
