/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:41:18 by llechert          #+#    #+#             */
/*   Updated: 2026/01/19 15:07:26 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	t_map	*map;

	if (ac != 2)
	{
		printf("Wrong number of arguments : ./cub3d map.cub\n");
		return (1);
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	if (!init_struct(game))
		return (1);
	set_floor_ceiling_color(game);
	// if (!parse(av[1], game))//Le parser stocke dans game les informations necessaires au jeu (cf. idees.txt)
	//     return (1);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (exit_game(game), 1);
	ft_memset(map, 0, sizeof(t_map));
	get_map(map, av[1]);//temporaire ?
	game->map = map;
	// print_map(map->grid);//debug only
	init_game(game);
	// print_minimap(game, game->mlx, game->img);
	mlx_loop(game->mlx->mlx_ptr);
	// exit_game(game);
	return (0);
}
