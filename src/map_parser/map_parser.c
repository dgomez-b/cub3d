#include "gnl/get_next_line.h"
#include "map_parser/map_parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils/utils.h"

void	free_textures(t_map *map)
{
	freedom((void **)&map->no_wall_texture);
	freedom((void **)&map->so_wall_texture);
	freedom((void **)&map->we_wall_texture);
	freedom((void **)&map->ea_wall_texture);
}

void	texture_error(t_map *map, char *line, int fd)
{
	write(STDOUT_FILENO, "Invalid texture ", 16);
	write(STDOUT_FILENO, line, ft_strlen(line));
	write(STDOUT_FILENO, "\n", 1);
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

void	color_error(t_map *map, char *line, int fd)
{
	write(STDOUT_FILENO, "Invalid color ", 14);
	write(STDOUT_FILENO, line, ft_strlen(line));
	write(STDOUT_FILENO, "\n", 1);
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
	write(STDOUT_FILENO, "The map couldn't be readed\n", 27);
	free_textures(map);
	exit (1);
}

void	map_error(t_map *map)
{
	write(STDOUT_FILENO, "Map resize failed\n", 18);
	free_textures(map);
	free_map_data(map);
	exit (1);
}

void	invalid_map(t_map *map)
{
	write(STDOUT_FILENO, "Invalid map\n", 12);
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

// FALTAN
//   - MAP_CHECK -> comprueba que no haya simbolos no validos (Los simbolos validos son ' ', '0', '1' y 'P')
//
// IMPORTANTE
//   - Un espacio (' ') dentro del area del mapa es un error
//   - No tener Jugador ('P') es un error
//   - Un 0 o Jugador ('P') fuera del area del mapa son errores

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
			write(STDOUT_FILENO, "Invalid file or read error\n", 27);
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
			write(STDOUT_FILENO, "Invalid file or read error\n", 27);
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
	int		counter;

	map_init(map);
	fd = open(map_path, O_RDONLY);
	store_textures(fd, map);
	store_colors(fd, map);
	store_map_data(fd, map);
	close(fd);
	if (!map->data)
		map_read_error(map);
	map_resize(map);
	if (map_check(map) == 1)
		invalid_map(map);
	printf("no -> %s\n", map->no_wall_texture);
	printf("we -> %s\n", map->we_wall_texture);
	printf("ea -> %s\n", map->ea_wall_texture);
	printf("so -> %s\n", map->so_wall_texture);
	printf("FLOOR -> 0x%X\n", map->floor);
	printf("FLOOR -> 0x%X\n", map->ceil);
	printf("\n");
	counter = 0;
	while (counter < map->height)
		printf("%s\n", map->data[counter++]);
}
