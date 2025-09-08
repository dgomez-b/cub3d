#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

// PERMITE TRANSPARENCIA
void	put_pixel(t_game *game, t_vector2D position, int color)
{
	char	*dst;

	if (position.x >= WIDTH || position.x < 0
		|| position.y >= HEIGHT || position.y < 0)
		return ;
	dst = game->data;
	dst += (int)position.y * game->size_line;
	dst += (int)position.x * (game->bpp / 8);
	*(unsigned int *)dst = color;
}

void	clear_image(t_game *game)
{
	t_vector2D	position;

	position.x = 0.0f;
	while (position.x < WIDTH)
	{
		position.y = 0.0f;
		while (position.y < HEIGHT)
		{
			put_pixel(game, position, 0x00000000);
			position.y++;
		}
		position.x++;
	}
}

// FUNCIÓN TEMPORAL
void	draw_square(t_game *game, t_vector2D position, unsigned int size,
	int color)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			put_pixel(game, (t_vector2D){position.x + x, position.y + y},
				color);
			y++;
		}
		x++;
	}
}

// FUNCIÓN TEMPORAL
void	draw_map(t_game *game)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 10)
		{
			if (g_map[y][x] == '1')
				draw_square(game, (t_vector2D){0 + (BLOCK_SIZE * x),
					0 + (BLOCK_SIZE * y)}, BLOCK_SIZE, 0x00FFFFFF);
			x++;
		}
		y++;
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
	const int	speed = 5;
	const float	angle_speed = 0.05f;

	if (player->left_pressed == TRUE)
		player->angle -= angle_speed;
	else if (player->right_pressed == TRUE)
		player->angle += angle_speed;
	if (player->angle >= (float)(2 * M_PI))
		player->angle -= (float)(2 * M_PI);
	else if (player->angle < 0)
		player->angle = 2 * M_PI - player->angle;
	if (player->w_pressed == TRUE)
		add_vector2d(&player->position, -(cos(player->angle) * speed),
			-(sin(player->angle) * speed));
	if (player->a_pressed == TRUE)
		add_vector2d(&player->position, -(sin(player->angle) * speed),
			cos(player->angle) * speed);
	if (player->s_pressed == TRUE)
		add_vector2d(&player->position, cos(player->angle) * speed,
			sin(player->angle) * speed);
	if (player->d_pressed == TRUE)
		add_vector2d(&player->position, sin(player->angle) * speed,
			-(cos(player->angle) * speed));
}

// FUNCIÓN A MODIFICAR EN EL FUTURO
int	draw_loop(t_game *game)
{
	t_vector2D	ray_pixel_pos;
	float		cos_angle;
	float		sin_angle;

	move_player(&game->player);
	clear_image(game);
	draw_map(game);
	draw_square(game, game->player.position, 20, 0x0000FF00);
	// printf("%.2f\n", game->player.angle * 180 / M_PI);
	ray_pixel_pos = game->player.position;
	ray_pixel_pos.x += 10;
	ray_pixel_pos.y += 10;
	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	while (!touch(ray_pixel_pos))
	{
		put_pixel(game, ray_pixel_pos, 0x00FF0000);
		ray_pixel_pos.x -= cos_angle;
		ray_pixel_pos.y -= sin_angle;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	return (0);
}

void	init_player(t_player *player)
{
	player->position.x = 110.0f;
	player->position.y = 110.0f;
	player->angle = M_PI_2;
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

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	init_player(&game->player);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->image, &game->bpp, &game->size_line,
			&game->endian);
	clear_image(game);
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
}

int	close_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->image);
	mlx_destroy_window(game->mlx, game->window);
	// freedom(game->mlx);
	exit(0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	draw_loop(&game);
	mlx_hook(game.window, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.window, 17, 1L << 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
