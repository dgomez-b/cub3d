/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:25:26 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/11/03 19:40:29 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

typedef struct s_map
{
	char		**data;
	int			width;
	int			height;
	int			floor;
	int			floor_stored;
	int			ceil;
	int			ceil_stored;
	char		*no_wall_texture;
	char		*we_wall_texture;
	char		*ea_wall_texture;
	char		*so_wall_texture;
}	t_map;

void	map_error(t_map *map);
void	map_resize(t_map *map);
void	map_init(t_map *map);
int		map_check(t_map *map);
int		map_check2(t_map *map);
void	map_parser(char *map_path, t_map *map);
void	invalid_map(t_map *map);
void	map_read_error(t_map *map);
void	free_map_data(t_map *map);
void	store_map_data(int fd, t_map *map);
void	color_error(t_map *map, char *line, int fd);
void	free_mat(void **mat);
void	line_to_rgb(char *line, int (*rgb)[]);
void	store_color(t_map *map, char *line, int fd);
void	free_textures(t_map *map);
void	texture_error(t_map *map, char *line, int fd);
void	store_texture(t_map *map, char *line, int fd);
void	store_map_bg_data1(int fd, char *first_line, t_map *map);
void	store_map_bg_data2(int fd, char *first_line, t_map *map);

#endif
