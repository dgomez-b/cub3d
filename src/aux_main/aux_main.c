/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:35:34 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/10/31 17:19:00 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
		while (position.y < HEIGHT / 2)
		{
			put_pixel(texture, position, 0x00000000);
			position.y++;
		}
		position.x++;
	}
}

void	paint_background(t_texture *texture, t_map *map)
{
	t_vector2D	position;

	position.x = 0.0f;
	while (position.x < WIDTH)
	{
		position.y = 0.0f;
		while (position.y < HEIGHT / 2.0f)
		{
			put_pixel(texture, position, map->ceil);
			position.y++;
		}
		while (position.y < HEIGHT)
		{
			put_pixel(texture, position, map->floor);
			position.y++;
		}
		position.x++;
	}
}

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
