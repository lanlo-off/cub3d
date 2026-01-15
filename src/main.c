/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:41:18 by llechert          #+#    #+#             */
/*   Updated: 2026/01/15 17:07:54 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		printf("Wrong number of arguments : ./cub3d map.cub\n");
		return (1);
	}
	if (!init_struct(game))
		return (1);
	// if (!parse(av[1], game))//Le parser stocke dans game les informations necessaires au jeu (cf. idees.txt)
	//     return (1);
	get_map(game->map, av[1]);//temporaire ?
	load_textures(game);
	// print_map(map->grid);//debug only
	init_game(game);
	// print_minimap(game, game->mlx, game->img);
	mlx_loop(game->mlx->mlx_ptr);
	exit_game(game);
	// free_all_exit(game);
	return (0);
}
