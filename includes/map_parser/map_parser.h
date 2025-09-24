#ifndef MAP_PARSER_H
# define MAP_PARSER_H

typedef struct s_map
{
	char		**data;
	int			width;
	int			height;
	int			floor;
	int			ceil;
	char		*no_wall_texture;
	int			no_wall_stored;
	char		*we_wall_texture;
	int			we_wall_stored;
	char		*ea_wall_texture;
	int			ea_wall_stored;
	char		*so_wall_texture;
	int			so_wall_stored;
}	t_map;

void	free_textures(t_map *map);
void	free_map_data(t_map *map);
void	map_parser(char *map_path, t_map *map);

#endif
