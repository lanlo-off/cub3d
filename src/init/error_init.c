/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:35:13 by llechert          #+#    #+#             */
/*   Updated: 2026/03/19 15:13:55 by llechert         ###   ########.fr       */
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
	if (game->tex_no)
		free_tex(game, game->tex_no);
	if (game->tex_so)
		free_tex(game, game->tex_so);
	if (game->tex_we)
		free_tex(game, game->tex_we);
	if (game->tex_ea)
		free_tex(game, game->tex_ea);
	if (game->c_color)
		free(game->c_color);
	if (game->f_color)
		free(game->f_color);
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
