/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:16:33 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/10/31 18:14:31 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"
#include "mlx/mlx.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	init_window(t_program *program, t_window *window)
{
	t_texture	background;

	program->window.width = 1080;
	program->window.height = 720;
	background.width = 1080;
	background.height = 720;
	window->mlx_ptr = mlx_new_window(program->mlx_ptr,
			window->width, window->height, "cub3d");
	background.mlx_ptr = mlx_new_image(program->mlx_ptr, background.width,
			background.height);
	background.data = mlx_get_data_addr(background.mlx_ptr, &background.bpp,
			&background.size_line, &background.endian);
	window->background = background;
	clear_texture(&window->background);
	mlx_put_image_to_window(program->mlx_ptr, window->mlx_ptr,
		background.mlx_ptr, 0, 0);
}

void	init_program(t_program *program)
{
	program->mlx_ptr = mlx_init();
	init_window(program, &program->window);
	mlx_hook(program->window.mlx_ptr, 17, 1L << 0, close_program, program);
}

void	load_texture(t_game *game, t_texture *texture, char *filename)
{
	texture->mlx_ptr = mlx_xpm_file_to_image(game->program.mlx_ptr, filename,
			&texture->width, &texture->height);
	if (!texture->mlx_ptr)
	{
		write(STDERR_FILENO, "Texture couldn't be loaded\n", 27);
		close_game(game);
	}
	texture->data = mlx_get_data_addr(texture->mlx_ptr, &texture->bpp,
			&texture->size_line, &texture->endian);
}

void	init_game(t_game *game)
{
	game->program.mlx_ptr = NULL;
	game->no_wall_texture.mlx_ptr = NULL;
	game->so_wall_texture.mlx_ptr = NULL;
	game->ea_wall_texture.mlx_ptr = NULL;
	game->we_wall_texture.mlx_ptr = NULL;
	check_texture_files_existance(game);
	init_player(&game->player, &game->map);
	init_program(&game->program);
	load_texture(game, &game->no_wall_texture,
		game->map.no_wall_texture);
	load_texture(game, &game->we_wall_texture,
		game->map.we_wall_texture);
	load_texture(game, &game->ea_wall_texture,
		game->map.ea_wall_texture);
	load_texture(game, &game->so_wall_texture,
		game->map.so_wall_texture);
	mlx_hook(game->program.window.mlx_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->program.window.mlx_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->program.window.mlx_ptr, 17, 1L << 0, close_game, game);
	mlx_loop_hook(game->program.mlx_ptr, player_loop, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		printf("You must give us the executable file and a map!\n");
	else if (argc == 2)
	{
		if (check_argv(argv[1]) == 0)
		{
			printf("That is not a valid format for a map!\n");
			return (0);
		}
		map_parser(argv[1], &game.map);
		init_game(&game);
		mlx_loop(game.program.mlx_ptr);
	}
	return (0);
}
