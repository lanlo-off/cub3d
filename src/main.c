/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:41:18 by llechert          #+#    #+#             */
/*   Updated: 2026/03/12 20:42:07 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return(printf("Wrong number of arguments : ./cub3d map.cub\n"), 1);
	if (is_file_valid(av[1], EXT_CUB) != EXT_CUB)
		return (1);
	printf(":Bon nb args et bon fichier\n");
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	game->map_path = av[1];
	if (!init_struct(game))
		return (1);
	printf(":intistruct\n");
	if (!parser(game))
		return (1);
	printf(":parser OK\n");
	print_map(game->map->grid); //debug only
	printf("DEBUG: map->grid = %p, width = %d, height = %d\n", 
		game->map->grid, game->map->width, game->map->height);
	if (game->map->grid && game->map->grid[0])
		printf("DEBUG: first line = '%s'\n", game->map->grid[0]);
	init_game(game);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}
