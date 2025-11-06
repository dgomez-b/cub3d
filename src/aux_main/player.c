/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:33:53 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/11/03 19:32:04 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	add_vector2d(t_vector2D *vec, float x, float y)
{
	vec->x += x;
	vec->y += y;
}

t_vector2D	player_map_position(t_map *map)
{
	t_vector2D	v_counter;

	v_counter.y = .5f;
	while (v_counter.y < map->height)
	{
		v_counter.x = .5f;
		while (v_counter.x < map->width
			&& map->data[(int)v_counter.y][(int)v_counter.x] != 'N'
			&& map->data[(int)v_counter.y][(int)v_counter.x] != 'S'
			&& map->data[(int)v_counter.y][(int)v_counter.x] != 'W'
			&& map->data[(int)v_counter.y][(int)v_counter.x] != 'E')
			v_counter.x++;
		if (v_counter.x < map->width)
			break ;
		v_counter.y++;
	}
	return ((t_vector2D){v_counter.x, v_counter.y});
}

void	init_player(t_player *player, t_map	*map)
{
	player->position = player_map_position(map);
	if (map->data[(int)player->position.y][(int)player->position.x] == 'N')
		player->angle = 3 * M_PI / 2;
	else if (map->data[(int)player->position.y][(int)player->position.x] == 'S')
		player->angle = M_PI / 2;
	else if (map->data[(int)player->position.y][(int)player->position.x] == 'W')
		player->angle = M_PI;
	else
		player->angle = 0;
	player->w_pressed = FALSE;
	player->a_pressed = FALSE;
	player->s_pressed = FALSE;
	player->d_pressed = FALSE;
	player->left_pressed = FALSE;
	player->right_pressed = FALSE;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	if (keycode == W)
		game->player.w_pressed = TRUE;
	if (keycode == A)
		game->player.a_pressed = TRUE;
	if (keycode == S)
		game->player.s_pressed = TRUE;
	if (keycode == D)
		game->player.d_pressed = TRUE;
	if (keycode == LEFT)
		game->player.left_pressed = TRUE;
	if (keycode == RIGHT)
		game->player.right_pressed = TRUE;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.w_pressed = FALSE;
	if (keycode == A)
		game->player.a_pressed = FALSE;
	if (keycode == S)
		game->player.s_pressed = FALSE;
	if (keycode == D)
		game->player.d_pressed = FALSE;
	if (keycode == LEFT)
		game->player.left_pressed = FALSE;
	if (keycode == RIGHT)
		game->player.right_pressed = FALSE;
	return (0);
}
