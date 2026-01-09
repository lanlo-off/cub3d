/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:35:13 by llechert          #+#    #+#             */
/*   Updated: 2026/01/09 10:16:46 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/**
 * @brief Echec en malloc game->img
 * Donc free ce qui a ete rempli par le parser
 * game->map
 * game->textures et chaque texture a l'interieur
 * game->img qui est initalise juste avant
 * puis game egalement
 * 
 * @param game 
 */
void	error_init_img(t_game *game)
{
	if (game->img)
		free(game->img);
	if (game->img->address)
		free(game->img->address);
	free_map(game->map);
	free_textures(game->textures);
	free(game->ceiling_color);//ou besoin d'une fonction ?
	free(game->floor_color);//ou besoin d'une fonction ?
	free(game);
	exit(1);
}

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
	error_init_img(game);
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
	if (mlx->mlx_ptr)//a voir si ce free est necessaire
		free(mlx->mlx_ptr);
	error_init_mlx(game);
}
