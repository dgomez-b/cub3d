NAME		=	cub3D
INC			=	./includes/
LIBS		=	./libs/
BIN			=	./.bin/
SRC			=	./src/
SRCS		=	main.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				utils/ft_strlcpy.c \
				utils/ft_strlen.c \
				utils/freedom.c \
				utils/ft_bzero.c \
				utils/ft_split.c \
				utils/ft_memset.c \
				utils/ft_calloc.c \
				utils/ft_strdup.c \
				utils/ft_atoi.c \
				map_parser/map_parser.c \
				map_parser/map_parser_aux.c \
				map_parser/textures.c \
				map_parser/colors.c \
				aux_main/aux_main.c \
				aux_main/aux_mainII.c \
				aux_main/aux_mainIII.c \
				aux_main/exit.c \
				aux_main/player.c

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
				@ $(CC) $(CFLAGS) -o $@ $^ -L$(dir $(MLX)) -lmlx -lXext -lX11 -lm -lz

# $(NAME)		:	$(MLX) $(OBJS)
# 				@ $(CC) $(CFLAGS) -o $@ $^ -L$(dir $(MLX)) -lmlx -framework \
# 					OpenGL -framework AppKit

clean		:
				@ rm -rfv $(BIN)
				@ make -sC $(dir $(MLX)) clean

fclean		:	clean
				@ rm -fv $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
