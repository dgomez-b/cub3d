/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-b <dgomez-b@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:05:57 by dgomez-b          #+#    #+#             */
/*   Updated: 2025/11/03 19:40:13 by dgomez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "map_parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void	map_bg_error(int fd, char *line, t_map *map)
{
	write(STDERR_FILENO, "Invalid map\n", 12);
	close(fd);
	freedom((void **)&line);
	free_textures(map);
	exit (1);
}

void	store_map_bg_data1(int fd, char *line, t_map *map)
{
	int		counter;

	counter = 0;
	while (counter++ < 2)
	{
		store_color(map, line, fd);
		line = get_next_line(fd);
	}
	if (!line || *line != '\n')
		map_bg_error(fd, line, map);
	while (line && *line == '\n')
	{
		freedom((void **)&line);
		line = get_next_line(fd);
	}
	counter = 0;
	while (counter++ < 4)
	{
		store_texture(map, line, fd);
		line = get_next_line(fd);
	}
	if (!line || *line != '\n')
		map_bg_error(fd, line, map);
	freedom((void **)&line);
}

void	store_map_bg_data2(int fd, char *line, t_map *map)
{
	int		counter;

	counter = 0;
	while (counter++ < 4)
	{
		store_texture(map, line, fd);
		line = get_next_line(fd);
	}
	if (!line || *line != '\n')
		map_bg_error(fd, line, map);
	while (line && *line == '\n')
	{
		freedom((void **)&line);
		line = get_next_line(fd);
	}
	counter = 0;
	while (counter++ < 2)
	{
		store_color(map, line, fd);
		line = get_next_line(fd);
	}
	if (!line || *line != '\n')
		map_bg_error(fd, line, map);
	freedom((void **)&line);
}
