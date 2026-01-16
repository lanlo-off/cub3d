/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:35:13 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 10:18:27 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Echec en malloc mlx->ptr ou initialisant la mlx
 * donc on free mlx->ptr si besoin
 * Puis appel de error_init_img qui exit
 * 
 * @param game 
 */
void	error_init_mlx(t_game *game)
{
	if (game->mlx)
		free(game->mlx);
	free_map(game->map);
	if (game->tex_NO)
		free_tex(game, game->tex_NO);
	if (game->tex_SO)
		free_tex(game, game->tex_SO);
	if (game->tex_WE)
		free_tex(game, game->tex_WE);
	if (game->tex_EA)
		free_tex(game, game->tex_EA);
	if (game->ceiling_color)
		free(game->ceiling_color);//ou besoin d'une fonction ?
	if (game->floor_color)
		free(game->floor_color);//ou besoin d'une fonction ?
	free(game);
	exit(1);
}
/**
 * @brief Echec en initialisant la fenetre
 * Donc destroy le pointeur vers la mlx
 * Puis appel de error_init_mlx
 * 
 * @param game 
 * @param mlx 
 */
void	error_init_win(t_game *game, t_mlx *mlx)
{
	mlx_destroy_display(mlx->mlx_ptr);
	if (mlx->mlx_ptr)
		free(mlx->mlx_ptr);
	error_init_mlx(game);
}

/**
 * @brief Echec en malloc game->img ou les fctions mlx de gen img
 * Donc free ce qui a ete rempli par le parser dans img
 * puis ca part sur la destruction de la mlx
 * 
 * @param game 
 */
void	error_init_img(t_game *game)
{
	if (!game->img)
		error_init_win(game, game->mlx);
	if (game->img->img_ptr)
		mlx_destroy_image(game->mlx->mlx_ptr, game->img->img_ptr);
	if (game->img->address)
		free(game->img->address);
	free(game->img);
	error_init_win(game, game->mlx);
}

void	error_init_player(t_game *game, t_player *player)
{
	if (player)
		free(player);
	error_init_img(game);
}
