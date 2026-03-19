/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:19:41 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/19 15:31:04 by llechert         ###   ########.fr       */
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
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	game->map_path = av[1];
	if (!init_struct(game))
		return (1);
	if (!parser(game))
		return (1);
	init_game(game);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}
