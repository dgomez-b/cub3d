#include "cub3d.h"
#include "map_parser/map_parser.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// char	g_map[40][50] = {
// {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
// {'1', 'P', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '1', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
// {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
// };

// void	freedom(void **ptr)
// {
// 	if (*ptr)
// 	{
// 		free(*ptr);
// 		*ptr = (void *)0;
// 	}
// }

void	add_vector2d(t_vector2D *vec, float x, float y)
{
	vec->x += x;
	vec->y += y;
}

// HAY QUE REDUCIR EL TAMAÑO DE ESTA FUNCIÓN O DIVIDIRLA EN MÁS FUNCIONES
void	move_player(t_player *player, t_game *game)
{
	const float	speed = 0.012f;
	const float	angle_speed = 0.008f;
	t_vector2D	target_pos;

	target_pos = player->position;
	if (player->left_pressed == TRUE)
		player->angle -= angle_speed;
	else if (player->right_pressed == TRUE)
		player->angle += angle_speed;
	if (player->angle >= (float)(2 * M_PI))
		player->angle -= (float)(2 * M_PI);
	else if (player->angle < 0)
		player->angle = 2 * M_PI - player->angle;
	if (player->w_pressed == TRUE)
		add_vector2d(&target_pos, (cos(player->angle) * speed),
			(sin(player->angle) * speed));
	if (player->a_pressed == TRUE)
		add_vector2d(&target_pos, (sin(player->angle) * speed),
			-cos(player->angle) * speed);
	if (player->s_pressed == TRUE)
		add_vector2d(&target_pos, -cos(player->angle) * speed,
			-sin(player->angle) * speed);
	if (player->d_pressed == TRUE)
		add_vector2d(&target_pos, -sin(player->angle) * speed,
			(cos(player->angle) * speed));
	if (target_pos.x >= 0 && target_pos.x < game->map.width && target_pos.y >= 0
		&& target_pos.y < game->map.height)
		player->position = target_pos;
}

void	init_player(t_player *player)
{
	player->position.x = 9.5f;
	player->position.y = 1.5f;
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

// --- los cambios inician aquí ---

void	ray_init(float angle, t_ray *ray, t_player *player)
{
	ray->dir = (t_vector2D){cosf(angle), sinf(angle)};
	ray->delta_dist = (t_vector2D){fabsf(1.0f / ray->dir.x),
			fabsf(1.0f / ray->dir.y)};
	ray->cell = (t_vector2D){(int)player->position.x, (int)player->position.y};
	ray->step.x = 1;
	ray->side_dist.x = ray->cell.x + 1.0f - player->position.x;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = player->position.x - ray->cell.x;
	}
	ray->side_dist.x *= ray->delta_dist.x;
	ray->step.y = 1;
	ray->side_dist.y = ray->cell.y + 1.0f - player->position.y;
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = player->position.y - ray->cell.y;
	}
	ray->side_dist.y *= ray->delta_dist.y;
}

void	ray_route(t_ray *ray, t_game *game)
{
	while (ray->cell.x >= 0 && ray->cell.x < game->map.width
		&& ray->cell.y >= 0 && ray->cell.y < game->map.height
		&& game->map.data[(int)ray->cell.y][(int)ray->cell.x] != '1')
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->cell.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->cell.y += ray->step.y;
			ray->side = 1;
		}
	}
}

void	ray_distance_calc(float angle, t_ray *ray, t_player *player)
{
	if ((ray->side == 0 && ray->step.x == 1) || (ray->side == 1 && ray->step.y == 1))
		ray->side += 2;
	if (ray->side % 2 == 0)
		ray->dist = (ray->cell.x - player->position.x + (1 - ray->step.x) / 2.0f) / ray->dir.x;
	else
		ray->dist = (ray->cell.y - player->position.y + (1 - ray->step.y) / 2.0f) / ray->dir.y;
	ray->dist *= cosf(angle - player->angle);
}

void	get_wall_height(t_wall_column *wall, t_ray ray, t_game *game)
{
	wall->wall_height = (int)(game->program.window.height / ray.dist);
	wall->start = (-wall->wall_height / 2 + game->program.window.height / 2);
	if (wall->start < 0)
		wall->draw_start = 0;
	else
		wall->draw_start = wall->start;
	wall->end = (wall->wall_height / 2 + game->program.window.height / 2);
	if (wall->end > game->program.window.height)
		wall->draw_end = game->program.window.height - 1;
	else
		wall->draw_end = wall->end;
}

void	texture_calc(t_wall_column *wall, t_ray ray, t_player *player, t_game *game)
{
	if (ray.side % 2 == 0)
		wall->wall_x = player->position.y + (ray.side_dist.x - ray.delta_dist.x)
			* ray.dir.y;
	else
		wall->wall_x = player->position.x + (ray.side_dist.y - ray.delta_dist.y)
			* ray.dir.x;
	wall->wall_x -= floor(wall->wall_x);
	wall->tex_x = (int)(wall->wall_x * game->no_wall_texture.width);
	if (ray.side == 0 || ray.side == 2)
		wall->tex_x = game->no_wall_texture.width - wall->tex_x - 1;
	if (ray.side == 0)
		wall->texture = &game->no_wall_texture;
	else if (ray.side == 1)
		wall->texture = &game->so_wall_texture;
	else if (ray.side == 2)
		wall->texture = &game->ea_wall_texture;
	else
		wall->texture = &game->we_wall_texture;
	wall->tex_y_step = (float)wall->texture->height / wall->wall_height;
	wall->tex_y_pos = (wall->draw_start - game->program.window.height / 2.0f
		+ wall->wall_height / 2.0f) * wall->tex_y_step;
}

void	texture_draw(t_wall_column *wall, int column, t_game *game)
{
	char	*column_ptr;
	int		counter;
	int		tex_y;
	int		color;

	column_ptr= game->program.window.background.data
		+ (wall->draw_start * game->program.window.background.size_line)
		+ (column * (game->program.window.background.bpp / 8));
	counter = wall->draw_start;
	while (counter++ < wall->draw_end)
	{
		tex_y = (int)wall->tex_y_pos & (wall->texture->height - 1); // Repetición vertical
		wall->tex_y_pos += wall->tex_y_step;
		// Copia el color directamente (sin put_pixel para evitar overhead)
		color = *(int *)(wall->texture->data
			+ (tex_y * wall->texture->size_line)
			+ (wall->tex_x * (wall->texture->bpp / 8)));
		*(int *)column_ptr = color;
		column_ptr += game->program.window.background.size_line; // Avanza al siguiente píxel en Y
	}
}

void	raycast(float angle, int column, t_player *player, t_game *game)
{
	t_ray			ray;
	t_wall_column	wall;

	ray_init(angle, &ray, player);
	ray_route(&ray, game);
	if (ray.cell.x < 0 || ray.cell.x >= game->map.width
		|| ray.cell.y < 0 || ray.cell.y >= game->map.height)
		return ;
	ray_distance_calc(angle, &ray, player);
	get_wall_height(&wall, ray, game);
	texture_calc(&wall, ray, player, game);
	texture_draw(&wall, column, game);
}

// // RAYCAST CON TEXTURAS (LARGO)
// void	raycast(float angle, int column, t_player *player, t_game *game)
// {
// 	const t_vector2D	ray_dir = {cosf(angle), sinf(angle)};
// 	const t_vector2D	delta_dist = {fabsf(1.0f / ray_dir.x),
// 			fabsf(1.0f / ray_dir.y)};
// 	t_vector2D			cell;
// 	t_vector2D			side_dist;
// 	t_vector2D			step;
// 	int					side;

// 	cell = (t_vector2D){(int)player->position.x, (int)player->position.y};
// 	if (ray_dir.x < 0)
// 	{
// 		step.x = -1;
// 		side_dist.x = (player->position.x - cell.x) * delta_dist.x;
// 	}
// 	else
// 		{ step.x = 1;  side_dist.x = (cell.x + 1.0f - player->position.x) * delta_dist.x; }
// 	if (ray_dir.y < 0)
// 	{
// 		step.y = -1;
// 		side_dist.y = (player->position.y - cell.y) * delta_dist.y;
// 	}
// 	else
// 		{ step.y = 1;  side_dist.y = (cell.y + 1.0f - player->position.y) * delta_dist.y; }

// 	// --- 2. DDA optimizado (evita recalcular delta_dist en cada iteración) ---
// 	while (g_map[(int)cell.y][(int)cell.x] != '1')
// 	{
// 		if (side_dist.x < side_dist.y)
// 		{
// 			side_dist.x += delta_dist.x;
// 			cell.x += step.x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist.y += delta_dist.y;
// 			cell.y += step.y;
// 			side = 1;
// 		}
// 	}

// 	// --- 3. Cálculo de distancia (optimizado) ---
// 	if ((side == 0 && step.x == 1) || (side == 1 && step.y == 1)) side += 2;
// 	float dist = (side % 2 == 0) ?
// 		(cell.x - player->position.x + (1 - step.x) / 2.0f) / ray_dir.x :
// 		(cell.y - player->position.y + (1 - step.y) / 2.0f) / ray_dir.y;
// 	dist *= cosf(angle - player->angle);

// 	// --- 4. Altura de la pared (evita recalcular wall_height/2 repetidamente) ---
// 	const int wall_height = (int)(game->program.window.height / dist);
// 	const int start = (-wall_height / 2 + game->program.window.height / 2);
// 	const int end = (wall_height / 2 + game->program.window.height / 2);
// 	int draw_start = (start < 0) ? 0 : start;
// 	int draw_end = (end > game->program.window.height) ? game->program.window.height - 1 : end;

// 	// --- 5. Cálculo de textura OPTIMIZADO (clave para rendimiento) ---
// 	// wall_x: posición exacta del impacto en la pared [0,1]
// 	float wall_x = (side % 2 == 0) ?
// 		player->position.y + (side_dist.x - delta_dist.x) * ray_dir.y :
// 		player->position.x + (side_dist.y - delta_dist.y) * ray_dir.x;
// 	wall_x -= floor(wall_x);

// 	// tex_x: coordenada X en la textura (0 a width-1)
// 	int tex_x = (int)(wall_x * game->no_wall_texture.width);
// 	if (side == 0 || side == 2) tex_x = game->no_wall_texture.width - tex_x - 1;

// 	// Selecciona la textura según la orientación (evita condicionales en el bucle)
// 	t_texture *texture = (side == 0) ? &game->no_wall_texture :
// 						 (side == 1) ? &game->so_wall_texture :
// 						 (side == 2) ? &game->ea_wall_texture :
// 						 &game->we_wall_texture;

// 	// Paso de textura en Y (precalculado fuera del bucle)
// 	const float tex_y_step = (float)texture->height / wall_height;
// 	float tex_y_pos = (draw_start - game->program.window.height / 2.0f
// 		+ wall_height / 2.0f) * tex_y_step;

// 	// --- 6. Dibujo optimizado (acceso lineal a memoria) ---
// 	// Usamos un puntero directo a la posición de memoria de la columna
// 	char *column_ptr = game->program.window.background.data
// 		+ (draw_start * game->program.window.background.size_line)
// 		+ (column * (game->program.window.background.bpp / 8));

// 	for (int y = draw_start; y < draw_end; y++)
// 	{
// 		int tex_y = (int)tex_y_pos & (texture->height - 1); // Repetición vertical
// 		tex_y_pos += tex_y_step;

// 		// Copia el color directamente (sin put_pixel para evitar overhead)
// 		int color = *(int *)(texture->data + (tex_y * texture->size_line) + (tex_x * (texture->bpp / 8)));
// 		*(int *)column_ptr = color;
// 		column_ptr += game->program.window.background.size_line; // Avanza al siguiente píxel en Y
// 	}
// }

// -- los cambios terminan aquí ---

// // RAYCAST SIN TEXTURAS (LARGO)
// void	raycast(float angle, int column, t_player *player, t_game *game)
// {
// 	const t_vector2D	ray_dir = {cosf(angle), sinf(angle)};
// 	t_vector2D			cell;
// 	t_vector2D			side_dist;
// 	const t_vector2D	delta_dist = {fabsf(1.0f / ray_dir.x),
// 			fabsf(1.0f / ray_dir.y)};
// 	t_vector2D			step;
// 	int					side;
// 	float				dist;

// 	cell.x = (int)player->position.x;
// 	cell.y = (int)player->position.y;
// 	if (ray_dir.x < 0)
// 	{
// 		step.x = -1;
// 		side_dist.x = (player->position.x - cell.x) * delta_dist.x;
// 	}
// 	else
// 	{
// 		step.x = 1;
// 		side_dist.x = (cell.x + 1.0f - player->position.x) * delta_dist.x;
// 	}
// 	if (ray_dir.y < 0)
// 	{
// 		step.y = -1;
// 		side_dist.y = (player->position.y - cell.y) * delta_dist.y;
// 	}
// 	else
// 	{
// 		step.y = 1;
// 		side_dist.y = (cell.y + 1.0f - player->position.y) * delta_dist.y;
// 	}
// 	while (1)
// 	{
// 		if (g_map[(int)cell.y][(int)cell.x] == '1')
// 			break ;
// 		if (side_dist.x < side_dist.y)
// 		{
// 			side_dist.x += delta_dist.x;
// 			cell.x += step.x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist.y += delta_dist.y;
// 			cell.y += step.y;
// 			side = 1;
// 		}
// 	}
// 	if ((side == 0 && step.x == 1) || (side == 1 && step.y == 1))
// 		side += 2;
// 	if (side % 2 == 0)
// 		dist = (cell.x - player->position.x + (1 - step.x) / 2.0f) / ray_dir.x;
// 	else
// 		dist = (cell.y - player->position.y + (1 - step.y) / 2.0f) / ray_dir.y;
// 	dist *= cosf(angle - player->angle);

// 	const int	wall_height = (int)(game->program.window.height / dist);
// 	int			start;
// 	int			end;
// 	int			current;

// 	start = (int)(-wall_height / 2 + game->program.window.height / 2);
// 	if (start < 0)
// 		start = 0;
// 	end = (int)(wall_height / 2 + game->program.window.height / 2);
// 	if (end > game->program.window.height)
// 		end = (int)game->program.window.height - 1;
// 	current = start;
// 	while (current < end)
// 	{
// 		int	color;

// 		if (side == 0)
// 			color = 0x0032CD32;
// 		else if (side == 1)
// 			color = 0x004682B4;
// 		else if (side == 2)
// 			color = 0x00DC143C;
// 		else
// 			color = 0x00BA55D3;
// 		put_pixel(&game->program.window.background,
// 				(t_vector2D){column, current++}, color);
// 	}
// }

void	draw_player_vision(t_player *player, t_game *game)
{
	const float	fov = M_PI / 4.0f;
	float		ray_angle;
	int			column;

	column = 0;
	while (column < game->program.window.width)
	{
		ray_angle = player->angle - (fov / 2.0f)
			+ (column * (fov / game->program.window.width));
		ray_angle = fmodf(ray_angle, 2.0f * M_PI);
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		raycast(ray_angle, column++, player, game);
	}
	mlx_put_image_to_window(game->program.mlx_ptr, game->program.window.mlx_ptr,
			game->program.window.background.mlx_ptr, 0, 0);
}

int	player_loop(t_game *game)
{
	move_player(&game->player, game);
	clear_texture(&game->program.window.background);
	draw_player_vision(&game->player, game);
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
	free_textures(&game->map);
	free_map_data(&game->map);
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

// void	init_map(t_game *game)
// {
// 	int		counter1;
// 	int		counter2;

// 	game->map = malloc(sizeof(char *) * 40);
// 	counter1 = 0;
// 	while (counter1 < game->map.height)
// 	{
// 		game->map.data[counter1] = malloc(sizeof(char) * 50);
// 		counter2 = 0;
// 		while (counter2 < game->map.width)
// 		{
// 			if (counter1 == 0 || counter1 == 39
// 				|| (counter2 == 0 || counter2 == 49))
// 				game->map.data[counter1][counter2++] = '1';
// 			else
// 				game->map.data[counter1][counter2++] = '0';
// 		}
// 		counter1++;
// 	}
// }

void	init_game(t_game *game)
{
	init_player(&game->player);
	init_program(&game->program);
	load_texture(&game->program, &game->no_wall_texture, game->map.no_wall_texture);
	load_texture(&game->program, &game->we_wall_texture, game->map.we_wall_texture);
	load_texture(&game->program, &game->ea_wall_texture, game->map.ea_wall_texture);
	load_texture(&game->program, &game->so_wall_texture, game->map.so_wall_texture);
	mlx_hook(game->program.window.mlx_ptr, 2, 1L << 0, key_press,
			&game->player);
	mlx_hook(game->program.window.mlx_ptr, 3, 1L << 1, key_release,
			&game->player);
	mlx_hook(game->program.window.mlx_ptr, 17, 1L << 0, close_game, game);
	mlx_loop_hook(game->program.mlx_ptr, player_loop, game);
}

int	main(void)
{
	t_game	game;

	// init_map(&game);
	map_parser("media/maps/map.map", &game.map);
	init_game(&game);
	mlx_loop(game.program.mlx_ptr);
	return (0);
}
