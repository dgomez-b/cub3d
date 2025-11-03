/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:08:18 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/09/26 18:20:10 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "map_parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void	free_textures(t_map *map)
{
	freedom((void **)&map->no_wall_texture);
	freedom((void **)&map->so_wall_texture);
	freedom((void **)&map->we_wall_texture);
	freedom((void **)&map->ea_wall_texture);
}

void	texture_error(t_map *map, char *line, int fd)
{
	write(STDERR_FILENO, "Invalid texture ", 16);
	write(STDERR_FILENO, line, ft_strlen(line));
	write(STDERR_FILENO, "\n", 1);
	freedom((void **)&line);
	close(fd);
	free_textures(map);
	exit (1);
}

void	store_texture(t_map *map, char *line, int fd)
{
	char	**texture;
	int		counter;

	if (line[0] == 'N' && line[1] == 'O' && *map->no_wall_texture == '\0')
		texture = &map->no_wall_texture;
	else if (line[0] == 'S' && line[1] == 'O' && *map->so_wall_texture == '\0')
		texture = &map->so_wall_texture;
	else if (line[0] == 'W' && line[1] == 'E' && *map->we_wall_texture == '\0')
		texture = &map->we_wall_texture;
	else if (line[0] == 'E' && line[1] == 'A' && *map->ea_wall_texture == '\0')
		texture = &map->ea_wall_texture;
	else
		texture_error(map, line, fd);
	counter = 2;
	while (line[counter] == ' ')
		counter++;
	*texture = ft_strdup(line + counter);
	(*texture)[ft_strlen(*texture) - 1] = '\0';
	if (!*texture)
		texture_error(map, line, fd);
}

void	store_textures(int fd, t_map *map)
{
	int		counter;
	char	*line;

	counter = 0;
	while (counter < 4)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			write(STDERR_FILENO, "Invalid file or read error\n", 27);
			free_textures(map);
			exit (1);
		}
		if (*line != '\n')
		{
			store_texture(map, line, fd);
			counter++;
		}
		freedom((void **)&line);
	}
}
