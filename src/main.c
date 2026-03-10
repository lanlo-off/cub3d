/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:41:18 by llechert          #+#    #+#             */
/*   Updated: 2026/03/10 12:10:35 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	t_map	*map;

	if (ac != 2)
		return(printf("Wrong number of arguments : ./cub3d map.cub\n"), 1);
	if (is_file_valid(av[1], EXT_CUB) != EXT_CUB)
		return (1);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	game->map_path = av[1];
	if (!init_struct(game))
		return (1);
	if (!parser(game))
		return (1);
	// print_map(map->grid); //debug only
	init_game(game);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}
