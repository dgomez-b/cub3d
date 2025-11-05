/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:16:01 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/11/03 19:31:39 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "map_parser.h"

# define WIDTH 1080
# define HEIGHT 720

# define BLOCK_SIZE 50

// // TECLAS MACOS (PUEDE QUE SEAN OTRAS)
// # define W      13
// # define A       0
// # define S       1
// # define D       2
// # define LEFT  123
// # define RIGHT 124
// # define ESC    53
// TECLAS LINUX (PUEDE QUE SEAN OTRAS)
# define W       119
# define A       97
# define S       115
# define D       100
# define LEFT  65361
# define RIGHT 65363
# define ESC   65307

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
	int			wall_height;
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

void	init_game(t_game *game);
void	load_texture(t_game *game, t_texture *texture, char *filename);
void	init_program(t_program *program);
void	init_window(t_program *program, t_window *window);
int		close_game(t_game *game);
int		close_program(t_program *program);
int		player_loop(t_game *game);
void	draw_player_vision(t_player *player, t_game *game);
void	raycast(float angle, int column, t_player *player, t_game *game);
void	texture_draw(t_wall_column *wall, int column, t_game *game);
void	clcltr(t_wall_column *wall, t_ray ray, t_player *player, t_game *game);
void	get_wall_height(t_wall_column *wall, t_ray ray, t_game *game);
void	ray_distance_calc(float angle, t_ray *ray, t_player *player);
void	ray_route(t_ray *ray, t_game *game);
void	ray_init(float angle, t_ray *ray, t_player *player);
float	distance(t_vector2D p1, t_vector2D p2);
void	clear_texture(t_texture *texture);
void	paint_background(t_texture *texture, t_map *map);
void	put_pixel(t_texture *texture, t_vector2D position, int color);
int		key_release(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);
void	init_player(t_player *player, t_map *map);
int		check_argv(char *str);
void	move_dir(t_vector2D *pos, float ang, float spd, t_player *p);
void	move_player(t_player *player, t_game *game);
void	add_vector2d(t_vector2D *vec, float x, float y);
void	check_texture_files_existance(t_game *game);

#endif
