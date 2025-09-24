#ifndef CUB3D_H
# define CUB3D_H

# include "map_parser/map_parser.h"

# define WIDTH 1080
# define HEIGHT 720

# define BLOCK_SIZE 50

# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
// // TECLAS LINUX (PUEDE QUE SEAN OTRAS)
// # define W 119
// # define A 97
// # define S 115
// # define D 100
// # define LEFT 123
// # define RIGHT 124

# include <math.h>
# include "mlx/mlx.h"

typedef struct s_vector2D
{
	float	x;
	float	y;
}	t_vector2D;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_player
{
	t_vector2D	position;
	float		angle;
	t_bool		w_pressed;
	t_bool		a_pressed;
	t_bool		s_pressed;
	t_bool		d_pressed;
	t_bool		left_pressed;
	t_bool		right_pressed;
}	t_player;

typedef struct s_texture
{
	void	*mlx_ptr;
	int		width;
	int		height;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_window
{
	void		*mlx_ptr;
	int			width;
	int			height;
	t_texture	background;
}	t_window;

typedef struct s_program
{
	void		*mlx_ptr;
	t_window	window;
}	t_program;

typedef struct s_game
{
	t_program	program;
	t_player	player;
	t_map		map;
	t_texture	no_wall_texture;
	t_texture	we_wall_texture;
	t_texture	ea_wall_texture;
	t_texture	so_wall_texture;
}	t_game;

typedef struct s_ray
{
	t_vector2D	dir;
	t_vector2D	cell;
	t_vector2D	delta_dist;
	t_vector2D	side_dist;
	t_vector2D	step;
	int			side;
	float		dist;
}	t_ray;

typedef struct s_wall_column
{
	int 		wall_height;
	int			start;
	int			end;
	int			draw_start;
	int			draw_end;
	float		wall_x;
	int			tex_x;
	t_texture	*texture;
	float		tex_y_step;
	float		tex_y_pos;
}	t_wall_column;

#endif
