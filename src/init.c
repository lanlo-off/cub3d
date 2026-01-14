/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:48:15 by llechert          #+#    #+#             */
/*   Updated: 2026/01/14 19:33:33 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	get_player_start(char **map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(i, j, map[i][j], player))
			{
				map[i][j] = '0';
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

static bool	init_struct_mlx(t_game* game, t_mlx *mlx)
{
	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		error_init_mlx(game);//Refaire toutes les fonctions d'exit en cas de fail
	game->mlx = mlx;
	mlx->win_width = WIN_WIDTH;
	mlx->win_height = WIN_HEIGHT;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		error_init_mlx(game);//Refaire toutes les fonctions d'exit en cas de fail
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->win_width, mlx->win_height, "NOM DE MAP");
	if (!mlx->win_ptr)
		error_init_win(game, game->mlx);//Refaire toutes les fonctions d'exit en cas de fail
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, key_press, game);//pour hook les key press
	mlx_hook(game->mlx->win_ptr, 3, 1L << 1, key_release, game);//pour hook les key releases
	mlx_hook(game->mlx->win_ptr, 17, 0, exit_game, game);//pour esc (et la croix ?)
	mlx_loop_hook(mlx->mlx_ptr, game_loop, game);
	return (true);
}

static bool	init_struct_img(t_game* game, t_img *img)
{
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		error_init_img(game);//Refaire toutes les fonctions d'exit en cas de fail
	game->img = img;
	// img->address = ft_calloc(1, sizeof(char *));
	// if (!img->address)
	// 	error_init_img(game);
	img->width = WIN_WIDTH;
	img->height = WIN_HEIGHT;
	
	//Peut-etre au'on aura d'autres choses a initaliser ?
	img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img->address = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	//Prevoir un return si les fopnctions mlx fail ?
	return (true);
}

bool	init_struct(t_game *game)
{
	game->tile_size = TILE_SIZE;
	init_struct_mlx(game, game->mlx);//Refaire toutes les fonctions d'exit en cas de fail
	init_struct_img(game, game->img);//Refaire toutes les fonctions d'exit en cas de fail
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		return (false);//et faire une fonction de sortie
	get_player_start(game->map->grid, game->player);
	game->key = ft_calloc(1, sizeof(t_key));
	if (!game->key)
		return (false);//et faire une fonction de sortie
	return (true);
}