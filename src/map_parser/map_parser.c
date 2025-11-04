/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:06:18 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/11/03 19:39:48 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "map_parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void	map_error(t_map *map)
{
	write(STDERR_FILENO, "Map resize failed\n", 18);
	free_textures(map);
	free_map_data(map);
	exit (1);
}

void	map_resize(t_map *map)
{
	int		counter;
	char	*line;
	int		line_end;

	counter = 0;
	while (counter < map->height)
	{
		line = malloc(sizeof(char) * map->width);
		if (!line)
			map_error(map);
		ft_memset(line, ' ', map->width);
		line_end = ft_strlcpy(line, map->data[counter],
				ft_strlen(map->data[counter])) - 1;
		if (line_end < map->width)
			line[line_end] = ' ';
		freedom((void **)(map->data + counter));
		map->data[counter++] = line;
	}
}

void	map_init(t_map *map)
{
	map->data = (void *)0;
	map->no_wall_texture = "\0";
	map->we_wall_texture = "\0";
	map->ea_wall_texture = "\0";
	map->so_wall_texture = "\0";
	map->floor = -1;
	map->ceil = -1;
	map->width = 0;
	map->height = 0;
}

int	map_check(t_map *map)
{
	int	line_counter;
	int	column_counter;

	line_counter = 0;
	while (line_counter < map->height)
	{
		column_counter = 0;
		while (column_counter < map->width)
		{
			if ((line_counter < map->height - 1 && line_counter > 0
					&& column_counter > 0 && column_counter < map->width - 1
					&& map->data[line_counter][column_counter] == '0'
				&& (map->data[line_counter][column_counter - 1] == ' '
				|| map->data[line_counter][column_counter + 1] == ' '
				|| map->data[line_counter + 1][column_counter] == ' '
				|| map->data[line_counter - 1][column_counter] == ' '))
				|| ((line_counter == map->height - 1 || line_counter == 0
					|| column_counter == map->width - 1 || column_counter == 0)
					&& map->data[line_counter][column_counter] == '0'))
				return (1);
			column_counter++;
		}
		line_counter++;
	}
	return (0);
}

void	map_parser(char *map_path, t_map *map)
{
	int		fd;
	char	*line;

	map_init(map);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("There has been a problem opening the map.\n");
		exit(0);
	}
	line = get_next_line(fd);
	if (line && (*line == 'F' || *line == 'C'))
		store_map_bg_data1(fd, line, map);
	else
		store_map_bg_data2(fd, line, map);
	line = (void *)0;
	store_map_data(fd, map);
	close(fd);
	if (!map->data)
		map_read_error(map);
	map_resize(map);
	if (map_check(map) == 1 || map_check2(map) == 1)
		invalid_map(map);
}
