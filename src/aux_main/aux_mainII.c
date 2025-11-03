/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_mainII.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:35:34 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/10/31 17:20:36 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ray_distance_calc(float angle, t_ray *ray, t_player *player)
{
	if ((ray->side == 0 && ray->step.x == 1)
		|| (ray->side == 1 && ray->step.y == 1))
		ray->side += 2;
	if (ray->side % 2 == 0)
		ray->dist = (ray->cell.x - player->position.x
				+ (1 - ray->step.x) / 2.0f) / ray->dir.x;
	else
		ray->dist = (ray->cell.y - player->position.y
				+ (1 - ray->step.y) / 2.0f) / ray->dir.y;
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

void	clcltr(t_wall_column *wall, t_ray ray, t_player *player, t_game *game)
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
		wall->texture = &game->we_wall_texture;
	else if (ray.side == 1)
		wall->texture = &game->no_wall_texture;
	else if (ray.side == 2)
		wall->texture = &game->ea_wall_texture;
	else
		wall->texture = &game->so_wall_texture;
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

	column_ptr = game->program.window.background.data
		+ (wall->draw_start * game->program.window.background.size_line)
		+ (column * (game->program.window.background.bpp / 8));
	counter = wall->draw_start;
	while (counter++ < wall->draw_end)
	{
		tex_y = (int)wall->tex_y_pos & (wall->texture->height - 1);
		wall->tex_y_pos += wall->tex_y_step;
		color = *(int *)(wall->texture->data
				+ (tex_y * wall->texture->size_line)
				+ (wall->tex_x * (wall->texture->bpp / 8)));
		*(int *)column_ptr = color;
		column_ptr += game->program.window.background.size_line;
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
	clcltr(&wall, ray, player, game);
	texture_draw(&wall, column, game);
}
