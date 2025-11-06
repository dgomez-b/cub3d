/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_mainIII.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:48:32 by ifluxa-c          #+#    #+#             */
/*   Updated: 2025/10/31 18:16:21 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"
#include "utils.h"
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	check_argv(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (str[len - 4] == '.' && str[len - 3] == 'c'
		&& str[len - 2] == 'u' && str[len - 1] == 'b')
		return (1);
	return (0);
}

void	move_dir(t_vector2D *pos, float ang, float spd, t_player *p)
{
	if (p->w_pressed)
		add_vector2d(pos, cos(ang) * spd, sin(ang) * spd);
	if (p->a_pressed)
		add_vector2d(pos, sin(ang) * spd, -cos(ang) * spd);
	if (p->s_pressed)
		add_vector2d(pos, -cos(ang) * spd, -sin(ang) * spd);
	if (p->d_pressed)
		add_vector2d(pos, -sin(ang) * spd, cos(ang) * spd);
}

void	move_player(t_player *p, t_game *g)
{
	const float	speed = 0.024f;
	const float	aspeed = 0.016f;
	t_vector2D	tpos;

	tpos = p->position;
	if (p->left_pressed)
		p->angle -= aspeed;
	else if (p->right_pressed)
		p->angle += aspeed;
	if (p->angle >= (float)(2 * M_PI))
		p->angle -= (float)(2 * M_PI);
	else if (p->angle <= 0)
		p->angle += (float)(2 * M_PI);
	move_dir(&tpos, p->angle, speed, p);
	if (tpos.x >= 0 && tpos.x < g->map.width && tpos.y >= 0
		&& tpos.y < g->map.height
		&& g->map.data[(int)tpos.y][(int)tpos.x] != '1')
		p->position = tpos;
}

void	check_texture_files_existance(t_game *game)
{
	int	texture_fds[4];

	texture_fds[0] = open(game->map.no_wall_texture, O_RDONLY);
	texture_fds[1] = open(game->map.so_wall_texture, O_RDONLY);
	texture_fds[2] = open(game->map.ea_wall_texture, O_RDONLY);
	texture_fds[3] = open(game->map.we_wall_texture, O_RDONLY);
	if (texture_fds[0])
		close(texture_fds[0]);
	if (texture_fds[1])
		close(texture_fds[1]);
	if (texture_fds[2])
		close(texture_fds[2]);
	if (texture_fds[3])
		close(texture_fds[3]);
	if (texture_fds[0] == -1 || texture_fds[1] == -1 || texture_fds[2] == -1
		|| texture_fds[3] == -1)
	{
		write(STDERR_FILENO, "Invalid texture\n", 16);
		close_game(game);
	}
}
