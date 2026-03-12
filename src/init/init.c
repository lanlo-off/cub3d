/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:48:15 by llechert          #+#    #+#             */
/*   Updated: 2026/03/12 19:51:01 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/**
 * @brief Permet de creer les coquilles des structures
 * game
 * game->map
 * game->key
 * game->textures
 * 
 * @param game 
 * @return true 
 * @return false 
 */
bool	init_struct(t_game *g)
{
	g->key = ft_calloc(1, sizeof(t_key));
	if (!g->key)
		return (free(g), false);
	printf("::init key\n");
	if (!init_map(g))
		return (free(g->key), free(g), false);
	printf("::init map\n");
	if (!init_textures(g)) //dans init_texture il y a aussi els couleurs
		return (free(g->key), free(g->map), free(g), false);
	printf("::init text + color\n");
	return (true);
}

static bool	init_struct_player(t_game *game, t_player *player)
{
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		error_init_player(game, player);
	if (!get_player_start(game->map->grid, game->player))
		error_init_player(game, player);
	// player->x = 10.5;
	// player->y = 10.5;
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
	if (!img->img_ptr || !img->address)
		error_init_img(game);
	return (true);
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

bool	init_game(t_game *game)
{
	game->tile_size = TILE_SIZE;
	printf("::init game\n");
	init_struct_mlx(game, game->mlx);
	printf("::init mlx\n");
	init_struct_img(game, game->img);
	printf("::init img\n");
	init_struct_player(game, game->player);
	printf("::init player\n");
	load_textures(game);
	printf("::load textures\n");
	return (true);
}