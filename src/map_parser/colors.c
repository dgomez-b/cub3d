/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:12:25 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/09/26 18:20:33 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "map_parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void	color_error(t_map *map, char *line, int fd)
{
	write(STDERR_FILENO, "Invalid color ", 14);
	write(STDERR_FILENO, line, ft_strlen(line));
	write(STDERR_FILENO, "\n", 1);
	close(fd);
	freedom((void **)&line);
	free_textures(map);
	exit (1);
}

void	free_mat(void **mat)
{
	int	counter;

	counter = 0;
	while (mat[counter])
		freedom((void **)(mat + counter++));
	freedom((void **)&mat);
}

void	line_to_rgb(char *line, int (*rgb)[])
{
	char	**crgb;
	int		counter;

	crgb = ft_split(line, ',');
	counter = 0;
	while (crgb[counter])
		counter++;
	if (counter != 3)
		(*rgb)[0] = -1;
	(*rgb)[0] = ft_atoi(crgb[0]);
	(*rgb)[1] = ft_atoi(crgb[1]);
	(*rgb)[2] = ft_atoi(crgb[2]);
	free_mat((void **)crgb);
}

void	store_color(t_map *map, char *line, int fd)
{
	int		*color;
	int		rgb[3];
	int		counter;

	if (*line == 'F' && map->floor == -1)
		color = &map->floor;
	else if (*line == 'C' && map->ceil == -1)
		color = &map->ceil;
	else
		color_error(map, line, fd);
	counter = 1;
	while (line[counter] == ' ')
		counter++;
	line_to_rgb(line + counter, &rgb);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[0] < 0
		|| rgb[0] > 255)
		color_error(map, line, fd);
	*color = ((00 & 0xFF) << 24) | ((rgb[0] & 0xFF) << 16)
		| ((rgb[1] & 0xFF) << 8) | (rgb[2] & 0xFF);
}

void	store_colors(int fd, t_map *map)
{
	int		counter;
	char	*line;

	counter = 0;
	while (counter < 2)
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
			store_color(map, line, fd);
			counter++;
		}
		freedom((void **)&line);
	}
}
