#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	g_map[8][10] = {
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
{'1', 'P', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

void	freedom(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = (void *)0;
	}
}

// FUNCIÓN A MODIFICAR EN EL FUTURO
t_bool	touch(t_vector2D position)
{
	const int	x = position.x / BLOCK_SIZE;
	const int	y = position.y / BLOCK_SIZE;

	if (g_map[y][x] == '1')
		return (TRUE);
	return (FALSE);
}

void	add_vector2d(t_vector2D *vec, float x, float y)
{
	vec->x += x;
	vec->y += y;
}

// HAY QUE REDUCIR EL TAMAÑO DE ESTA FUNCIÓN O DIVIDIRLA EN MÁS FUNCIONES
void	move_player(t_player *player)
{
	const float	speed = 0.02f;
	const float	angle_speed = 0.01f;

	if (player->left_pressed == TRUE)
		player->angle -= angle_speed;
	else if (player->right_pressed == TRUE)
		player->angle += angle_speed;
	if (player->angle >= (float)(2 * M_PI))
		player->angle -= (float)(2 * M_PI);
	else if (player->angle < 0)
		player->angle = 2 * M_PI - player->angle;
	if (player->w_pressed == TRUE)
		add_vector2d(&player->position, (cos(player->angle) * speed),
			(sin(player->angle) * speed));
	if (player->a_pressed == TRUE)
		add_vector2d(&player->position, (sin(player->angle) * speed),
			-cos(player->angle) * speed);
	if (player->s_pressed == TRUE)
		add_vector2d(&player->position, -cos(player->angle) * speed,
			-sin(player->angle) * speed);
	if (player->d_pressed == TRUE)
		add_vector2d(&player->position, -sin(player->angle) * speed,
			(cos(player->angle) * speed));
}

void	init_player(t_player *player)
{
	player->position.x = 2.5f;
	player->position.y = 2.5f;
	player->angle = 3 * M_PI / 2;
	player->w_pressed = FALSE;
	player->a_pressed = FALSE;
	player->s_pressed = FALSE;
	player->d_pressed = FALSE;
	player->left_pressed = FALSE;
	player->right_pressed = FALSE;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->w_pressed = TRUE;
	if (keycode == A)
		player->a_pressed = TRUE;
	if (keycode == S)
		player->s_pressed = TRUE;
	if (keycode == D)
		player->d_pressed = TRUE;
	if (keycode == LEFT)
		player->left_pressed = TRUE;
	if (keycode == RIGHT)
		player->right_pressed = TRUE;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->w_pressed = FALSE;
	if (keycode == A)
		player->a_pressed = FALSE;
	if (keycode == S)
		player->s_pressed = FALSE;
	if (keycode == D)
		player->d_pressed = FALSE;
	if (keycode == LEFT)
		player->left_pressed = FALSE;
	if (keycode == RIGHT)
		player->right_pressed = FALSE;
	return (0);
}

// PERMITE TRANSPARENCIA
void	put_pixel(t_texture *texture, t_vector2D position, int color)
{
	char	*dst;

	if (position.x >= texture->width || position.x < 0
		|| position.y >= texture->height || position.y < 0)
		return ;
	dst = texture->data;
	dst += (int)position.y * texture->size_line;
	dst += (int)position.x * (texture->bpp / 8);
	*(unsigned int *)dst = color;
}

void	clear_texture(t_texture *texture)
{
	t_vector2D	position;

	position.x = 0.0f;
	while (position.x < WIDTH)
	{
		position.y = 0.0f;
		while (position.y < HEIGHT)
		{
			put_pixel(texture, position, 0x00000000);
			position.y++;
		}
		position.x++;
	}
}

float	distance(t_vector2D p1, t_vector2D p2)
{
	t_vector2D	vec;

	vec.x = p1.x - p2.x;
	vec.y = p1.y - p2.y;
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

// --- SEGMENTO DE CODIGO TEMPORAL (O PARA EL BONUS DEL MINIMAPA)

// FUNCIÓN TEMPORAL

// void	draw_square(t_texture *texture, t_vector2D position, unsigned int size,
// 	int color)
// {
// 	unsigned int	x;
// 	unsigned int	y;

// 	x = 0;
// 	while (x < size)
// 	{
// 		y = 0;
// 		while (y < size)
// 		{
// 			put_pixel(texture, (t_vector2D){position.x + x, position.y + y},
// 				color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// // FUNCIÓN TEMPORAL
// void	draw_map(t_texture *texture)
// {
// 	unsigned int	x;
// 	unsigned int	y;

// 	y = 0;
// 	while (y < 8)
// 	{
// 		x = 0;
// 		while (x < 10)
// 		{
// 			if (g_map[y][x] == '1')
// 				draw_square(texture, (t_vector2D){0 + (40 * x),
// 					0 + (40 * y)}, 40, 0x00FFFFFF);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// --- FIN SEGMENTO

// FUNCIÓN A MODIFICAR EN EL FUTURO

void	raycast(float angle, int column, t_game *game)
{
	const t_vector2D	ray_dir = {cosf(angle), sinf(angle)};
	t_vector2D			cell;
	t_vector2D			side_dist;
	const t_vector2D	delta_dist = {fabsf(1.0f / ray_dir.x),
			fabsf(1.0f / ray_dir.y)};
	t_vector2D			step;
	int					side;
	float				dist;

	cell.x = (int)game->player.position.x;
	cell.y = (int)game->player.position.y;
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (game->player.position.x - cell.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (cell.x + 1.0f - game->player.position.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (game->player.position.y - cell.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (cell.y + 1.0f - game->player.position.y) * delta_dist.y;
	}
	while (1)
	{
		if (g_map[(int)cell.y][(int)cell.x] == '1')
			break ;
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			cell.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			cell.y += step.y;
			side = 1;
		}
	}
	if ((side == 0 && step.x == 1) || (side == 1 && step.y == 1))
		side += 2;
	if (side % 2 == 0)
		dist = (cell.x - game->player.position.x + (1 - step.x) / 2.0f) / ray_dir.x;
	else
		dist = (cell.y - game->player.position.y + (1 - step.y) / 2.0f) / ray_dir.y;
	dist *= cosf(angle - game->player.angle);

	const int	wall_height = (int)(game->program.window.height / dist);
	int			start;
	int			end;
	int			current;

	start = (int)(-wall_height / 2 + game->program.window.height / 2);
	if (start < 0)
		start = 0;
	end = (int)(wall_height / 2 + game->program.window.height / 2);
	if (end > game->program.window.height)
		end = (int)game->program.window.height - 1;
	current = start;
	while (current < end)
	{
		int	color;

		if (side == 0)
			color = 0x0032CD32;
		else if (side == 1)
			color = 0x004682B4;
		else if (side == 2)
			color = 0x00DC143C;
		else
			color = 0x00BA55D3;
		put_pixel(&game->program.window.background,
				(t_vector2D){column, current++}, color);
	}
}

int	draw_loop(t_game *game)
{
	const float	fov = M_PI / 4;
	float	ray_angle;

	move_player(&game->player);
	clear_texture(&game->program.window.background);
	// draw_map(&game->program.window.background);
	// draw_square(&game->program.window.background, game->player.position, 20, 0x0000FF00);
	// printf("%.2f\n", game->player.angle * 180 / M_PI);
	for (int x = 0; x < game->program.window.width; x++)
	{
		ray_angle = game->player.angle - (fov / 2) + (x * (fov / game->program.window.width));
		ray_angle = fmodf(ray_angle, 2 * M_PI);
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		raycast(ray_angle, x, game);
	}
	mlx_put_image_to_window(game->program.mlx_ptr, game->program.window.mlx_ptr,
			game->program.window.background.mlx_ptr, 0, 0);
	return (0);
}

int	close_program(t_program *program)
{
	// write(STDOUT_FILENO, "CIERRE DEL PROGRAMA\n", 20); // PARA DEBUG
	mlx_destroy_image(program->mlx_ptr, program->window.background.mlx_ptr);
	mlx_destroy_window(program->mlx_ptr, program->window.mlx_ptr);
	exit (0);
}

int	close_game(t_game *game)
{
	// write(STDOUT_FILENO, "CIERRE DEL JUEGO\n", 17); // PARA DEBUG
	mlx_destroy_image(game->program.mlx_ptr, game->no_wall_texture.mlx_ptr);
	mlx_destroy_image(game->program.mlx_ptr, game->we_wall_texture.mlx_ptr);
	mlx_destroy_image(game->program.mlx_ptr, game->ea_wall_texture.mlx_ptr);
	mlx_destroy_image(game->program.mlx_ptr, game->so_wall_texture.mlx_ptr);
	close_program(&game->program);
	exit(0);
}

void	init_window(t_program *program, t_window *window)
{
	t_texture	background;

	program->window.width = 1080;
	program->window.height = 720;
	background.width = 1080;
	background.height = 720;
	window->mlx_ptr = mlx_new_window(program->mlx_ptr,
			window->width, window->height, "cub3d");
	background.mlx_ptr = mlx_new_image(program->mlx_ptr, background.width,
			background.height);
	background.data = mlx_get_data_addr(background.mlx_ptr, &background.bpp,
			&background.size_line, &background.endian);
	window->background = background;
	clear_texture(&window->background);
	mlx_put_image_to_window(program->mlx_ptr, window->mlx_ptr,
			background.mlx_ptr, 0, 0);
}

void	init_program(t_program *program)
{
	program->mlx_ptr = mlx_init();
	init_window(program, &program->window);
	mlx_hook(program->window.mlx_ptr, 17, 1L << 0, close_program, program);
}

void	load_texture(t_program *program, t_texture *texture, char *filename)
{
	texture->mlx_ptr = mlx_xpm_file_to_image(program->mlx_ptr, filename,
			&texture->width, &texture->height);
	texture->data = mlx_get_data_addr(texture->mlx_ptr, &texture->bpp,
			&texture->size_line, &texture->endian);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	init_program(&game->program);
	load_texture(&game->program, &game->no_wall_texture, "media/wall.xpm");
	load_texture(&game->program, &game->we_wall_texture, "media/stone.xpm");
	load_texture(&game->program, &game->ea_wall_texture, "media/wall.xpm");
	load_texture(&game->program, &game->so_wall_texture, "media/stone.xpm");
	mlx_hook(game->program.window.mlx_ptr, 2, 1L << 0, key_press,
			&game->player);
	mlx_hook(game->program.window.mlx_ptr, 3, 1L << 1, key_release,
			&game->player);
	mlx_hook(game->program.window.mlx_ptr, 17, 1L << 0, close_game, game);
	mlx_loop_hook(game->program.mlx_ptr, draw_loop, game);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_loop(game.program.mlx_ptr);
	return (0);
}
