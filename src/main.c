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

float	distance(t_vector2D p1, t_vector2D p2)
{
	t_vector2D	vec;

	vec.x = p1.x - p2.x;
	vec.y = p1.y - p2.y;
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

void	raycast(float angle, int column, t_game *game)
{
	const float	angle_cos = cosf(angle);
	const float	angle_sin = sinf(angle);
	t_vector2D	cell;
	t_vector2D	delta;
	t_vector2D	side_dist;
	t_vector2D	step;
	int			side;
	float		dist;

	cell.x = trunc(game->player.position.x);
	cell.y = trunc(game->player.position.y);
	delta.x = fabsf(1.0f / angle_cos);
	delta.y = fabsf(1.0f / angle_sin);
	if (angle_cos < 0)
	{
		step.x = -1;
		side_dist.x = (game->player.position.x - cell.x) * delta.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (cell.x + 1.0f - game->player.position.x) * delta.x;
	}
	if (angle_sin < 0)
	{
		step.y = -1;
		side_dist.y = (game->player.position.y - cell.y) * delta.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (cell.y + 1.0f - game->player.position.y) * delta.y;
	}
	while (g_map[(int)cell.y][(int)cell.x] != '1')
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta.x;
			cell.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta.y;
			cell.y += step.y;
			side = 1;
		}
	}
	if (side == 0)
		dist = (cell.x - game->player.position.x + (1 - step.x) / 2) / angle_cos;
	else
		dist = (cell.y - game->player.position.y + (1 - step.y) / 2) / angle_sin;
	float ray_angle_diff = angle - game->player.angle;
	dist *= cosf(ray_angle_diff);


	float	lineHeight;
	int		start;
	int		end;

	lineHeight = (1.0f / dist) * (WIDTH / 2.0f);
	start = (int)truncf((HEIGHT - lineHeight) / 2.0f);
	end = (int)truncf(start + lineHeight);
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	// printf("%d, %d\n", start, end);
	while (start < end)
		put_pixel(game, (t_vector2D){column, start++}, 0x00808080); // gris
}

// FUNCIÓN A MODIFICAR EN EL FUTURO
int	draw_loop(t_game *game)
{
	float	angle;
	int		column;
	float	fraction;

	move_player(&game->player);
	clear_image(game);
	// draw_map(game);
	// draw_square(game, game->player.position, 20, 0x0000FF00);
	// printf("%.2f\n", game->player.angle * 180 / M_PI);
	angle = game->player.angle - (M_PI / 6);
	if (angle < 0)
		angle += 2 * M_PI;
	fraction = M_PI / 3 / WIDTH;
	column = 0;
	while (column < WIDTH)
	{
		raycast(angle, column, game);
		angle += fraction;
		column++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	return (0);
}

void	init_player(t_player *player)
{
	player->position.x = 2.3f;
	player->position.y = 2.3f;
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
