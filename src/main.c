/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:41:18 by llechert          #+#    #+#             */
/*   Updated: 2026/01/06 18:38:09 by llechert         ###   ########.fr       */
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
	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		return (1);
	// if (!parse(av[1], game))//ici on remplit "game->map", "game->textures", "game->ceiling_color" et "game->floor_color"
		//return (1);
	init_struct(game);
	print_minimap(game);
	// free_all_exit(game);
	return (0);
}
