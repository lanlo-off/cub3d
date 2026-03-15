/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mmiotla <mmiotla@student.42.fr>           #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/03 13:19:41 by mmiotla          #+#    #+#              */
/*   Updated: 2026/03/15 18:52:39 by mmiotla         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (printf(MSG_ERR_ARG), 1);
	if (is_file_valid(av[1], EXT_CUB) != EXT_CUB)
		return (printf(MSG_ERR_FILE_EXT), 1);
	//printf(":Bon nb args et bon fichier\n");
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	game->map_path = av[1];
	if (!init_struct(game))
		return (1);
	//printf(":intistruct\n");
	if (!parser(game))
		return ( 1);
	//printf(":parser OK\n");
	// print_map(game->map->grid); //debug only
	// printf("DEBUG: map->grid = %p, width = %d, height = %d\n",
	// 	game->map->grid, game->map->width, game->map->height);
	// if (game->map->grid && game->map->grid[0])
	// 	printf("DEBUG: first line = '%s'\n", game->map->grid[0]);
	init_game(game);
	mlx_loop(game->mlx->mlx_ptr);
	free(game);
	return (0);
}
