/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:48:15 by llechert          #+#    #+#             */
/*   Updated: 2026/01/07 17:44:23 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	init_struct_mlx(t_game* game, t_mlx *mlx)
{
	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		error_init_mlx(game);
	game->mlx = mlx;
	mlx->win_width = WIN_WIDTH;
	mlx->win_height = WIN_HEIGHT;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		error_init_mlx(game);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->win_width, mlx->win_height, "NOM DE MAP");
	if (!mlx->win_ptr)
		error_init_win(game, game->mlx);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, NULL, game);//pour hook les deplacements
	// mlx_hook(data->win_ptr, 2, 1L << 0, handle_cam, game);//pour hook les mouvements de camera
	mlx_hook(game->mlx->win_ptr, 17, 0, exit_game, game);//pour esc (et la croix ?)
	return (true);
}

static bool	init_struct_img(t_game* game, t_img *img)
{
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		error_init_img(game);
	game->img = img;
	img->address = ft_calloc(1, sizeof(char *));
	if (!img->address)
		error_init_img(game);
	//Peut-etre au'on aura d'autres choses a initaliser ?
	return (true);
}

bool	init_struct(t_game *game)
{
	game->tile_size = TILE_SIZE;
	init_struct_img(game, game->img);
	init_struct_mlx(game, game->mlx);//on exit dedans si fail
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		return (false);//et faire une fonction de sortie
	return (true);
}