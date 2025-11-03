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
#include "mlx/mlx.h"
#include "utils.h"
#include <math.h>
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
	else if (p->angle < 0)
		p->angle = 2 * M_PI - p->angle;
	move_dir(&tpos, p->angle, speed, p);
	if (tpos.x >= 0 && tpos.x < g->map.width && tpos.y >= 0
		&& tpos.y < g->map.height
		&& g->map.data[(int)tpos.y][(int)tpos.x] != '1')
		p->position = tpos;
}
