/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:16:33 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/10/31 17:46:50 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	paint_background(&game->program.window.background, &game->map);
	draw_player_vision(&game->player, game);
	return (0);
}

int	close_program(t_program *program)
{
	if (program->window.mlx_ptr != NULL)
	{
		mlx_destroy_image(program->mlx_ptr, program->window.background.mlx_ptr);
		mlx_destroy_window(program->mlx_ptr, program->window.mlx_ptr);
		mlx_destroy_display(program->mlx_ptr);
		free(program->mlx_ptr);
	}
	exit (0);
}

int	close_game(t_game *game)
{
	free_textures(&game->map);
	free_map_data(&game->map);
	if (game->no_wall_texture.mlx_ptr)
		mlx_destroy_image(game->program.mlx_ptr, game->no_wall_texture.mlx_ptr);
	if (game->we_wall_texture.mlx_ptr)
		mlx_destroy_image(game->program.mlx_ptr, game->we_wall_texture.mlx_ptr);
	if (game->ea_wall_texture.mlx_ptr)
		mlx_destroy_image(game->program.mlx_ptr, game->ea_wall_texture.mlx_ptr);
	if (game->so_wall_texture.mlx_ptr)
		mlx_destroy_image(game->program.mlx_ptr, game->so_wall_texture.mlx_ptr);
	if (game->program.mlx_ptr)
		close_program(&game->program);
	exit(0);
}

float	distance(t_vector2D p1, t_vector2D p2)
{
	t_vector2D	vec;

	vec.x = p1.x - p2.x;
	vec.y = p1.y - p2.y;
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}
