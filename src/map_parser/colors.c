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

#include "map_parser.h"
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void	color_error(t_map *map, char *line, int fd)
{
	write(STDERR_FILENO, "Invalid color\n", 15);
	close(fd);
	freedom((void **)&line);
	free_textures(map);
	exit (1);
}

static void	double_color_error(t_map *map, char *line, int fd)
{
	write(STDERR_FILENO, "Duplicated color\n", 17);
	close(fd);
	freedom((void **)&line);
	free_textures(map);
	exit (1);
}

// void	free_mat(void **mat)
// {
// 	int	counter;

// 	counter = 0;
// 	while (mat[counter])
// 		freedom((void **)(mat + counter++));
// 	freedom((void **)&mat);
// }

// void	line_to_rgb(char *line, int (*rgb)[])
// {
// 	char	**crgb;
// 	int		counter;

// 	crgb = ft_split(line, ',');
// 	counter = 0;
// 	while (crgb[counter])
// 		counter++;
// 	if (counter != 3)
// 		(*rgb)[0] = -1;
// 	(*rgb)[0] = ft_atoi(crgb[0]);
// 	(*rgb)[1] = ft_atoi(crgb[1]);
// 	(*rgb)[2] = ft_atoi(crgb[2]);
// 	free_mat((void **)crgb);
// }

// void	store_color(t_map *map, char *line, int fd)
// {
// 	int		*color;
// 	int		rgb[3];
// 	int		counter;

// 	if (!line || ft_strlen(line) <= 2 || line[1] != ' ')
// 		color_error(map, line, fd);
// 	if (*line == 'F' && map->floor == -1)
// 		color = &map->floor;
// 	else if (*line == 'C' && map->ceil == -1)
// 		color = &map->ceil;
// 	else
// 		color_error(map, line, fd);
// 	counter = 1;
// 	while (line[counter] == ' ')
// 		counter++;
// 	line_to_rgb(line + counter, &rgb);
// 	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[0] < 0
// 		|| rgb[0] > 255)
// 		color_error(map, line, fd);
// 	*color = ((00 & 0xFF) << 24) | ((rgb[0] & 0xFF) << 16)
// 		| ((rgb[1] & 0xFF) << 8) | (rgb[2] & 0xFF);
// 	freedom((void **)&line);
// }

static int	*get_target_color(t_map *map, char *line, int fd)
{
	if (line[0] == 'F')
	{
		if (map->floor_stored == 1)
			double_color_error(map, line, fd);
		map->floor_stored = 1;
		return (&map->floor);
	}
	else
	{
		if (map->ceil_stored == 1)
			double_color_error(map, line, fd);
		map->ceil_stored = 1;
		return (&map->ceil);
	}
}

static int	get_next_value(char **line)
{
	int	value;

	if (**line == ',')
		return (-1);
	value = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	return (value);
}

void	store_color(t_map *map, char *line, int fd)
{
	int		*target;
	int		values[3];
	char	*aux;

	aux = line;
	if ((aux[0] != 'F' && aux[0] != 'C') || aux[1] != ' ')
		color_error(map, line, fd);
	target = get_target_color(map, line, fd);
	while (*(++aux) == ' ')
		continue ;
	values[0] = get_next_value(&aux);
	if (aux[0] != ',' || aux[1] == '\n')
		color_error(map, line, fd);
	aux++;
	values[1] = get_next_value(&aux);
	if (aux[0] != ',' || aux[1] == '\n')
		color_error(map, line, fd);
	aux++;
	values[2] = get_next_value(&aux);
	if (values[0] < 0 || values[0] > 255 || values[1] < 0 || values[1] > 255
		|| values[2] < 0 || values[2] > 255 || aux[0] != '\n')
		color_error(map, line, fd);
	*target = ((00 & 0xFF) << 24) | ((values[0] & 0xFF) << 16)
		| ((values[1] & 0xFF) << 8) | (values[2] & 0xFF);
	freedom((void **)&line);
}
