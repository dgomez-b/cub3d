/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:05:57 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/11/03 19:40:13 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "map_parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void	store_map_data(int fd, t_map *map)
{
	char		*line;
	static int	err = 0;
	int			height;

	line = get_next_line(fd);
	while (line && *line == '\n' && map->height == 0)
	{
		freedom((void **)&line);
		line = get_next_line(fd);
	}
	if (!line)
		return ;
	if ((ft_strlen(line) - 1) > (size_t)map->width)
		map->width = ft_strlen(line) - 1;
	height = map->height;
	map->height = height + 1;
	store_map_data(fd, map);
	if (!map->data && err == 0)
		map->data = malloc(sizeof(char *) * map->height);
	if (!map->data)
	{
		err = 1;
		return (freedom((void **)&line));
	}
	map->data[height] = line;
}

void	free_map_data(t_map *map)
{
	int	counter;

	counter = 0;
	while (counter < map->height)
		freedom((void **)(map->data + counter++));
	freedom((void **)&map->data);
}

void	map_read_error(t_map *map)
{
	write(STDERR_FILENO, "The map couldn't be readed\n", 27);
	free_textures(map);
	exit (1);
}

void	invalid_map(t_map *map)
{
	write(STDERR_FILENO, "Invalid map\n", 12);
	free_textures(map);
	free_map_data(map);
	exit (1);
}

int	map_check2(t_map *map)
{
	int	found_player;
	int	x;
	int	y;

	found_player = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->data[y][x] == 'N' || map->data[y][x] == 'S'
				|| map->data[y][x] == 'W' || map->data[y][x] == 'E')
			{
				if (!found_player)
					found_player = 1;
				else
					return (1);
			}
			else if (map->data[y][x] != '0' && map->data[y][x] != '1'
				&& map->data[y][x] != ' ')
				return (1);
		}
	}
	return ((found_player + 1) % 2);
}
