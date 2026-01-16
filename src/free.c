/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:11:42 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 10:29:07 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_img(t_img *img)
{
	free(img);
}

void	free_mlx(t_mlx *mlx)
{
	mlx_destroy_display(mlx->mlx_ptr);
	if (mlx->mlx_ptr)//a voir si ce free est necessaire
		free(mlx->mlx_ptr);
	free(mlx);
}

/**
 * @brief Free la map
 * En cas d'echec d'init ou de fin normale du jeu
 * 
 * @param map 
 */
void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}

/**
 * @brief Free chacune des textures
 * En cas d'echec d'init ou de fin normale du jeu
 * 
 * @param textures 
 */
void	free_tex(t_game *g, t_tex *texture)
{
	if (!texture)
		return ;
	if (texture->img)
		mlx_destroy_image(g->mlx->mlx_ptr, texture->img);
	free(texture);
}

/**
 * @brief Doit pouvoir tout free
 * Voir si game->mlx, game->player etc... doivent etre free ou si ce sont des coquilles
 * qui seront free avec l'instruction free(game) ?
 * 
 * @param game 
 * @return int 
 */
int	exit_game(t_game *game)
{
	if (!game)
		return (0);
	if (game->ceiling_color)
		free(game->ceiling_color);
	if (game->floor_color)
		free(game->floor_color);
	if (game->img)
		free_img(game->img);
	if (game->map)
		free_map(game->map);
	if (game->mlx)
		free_mlx(game->mlx);
	if (game->player)
		free(game->player);
	if (game->tex_NO)
		free_tex(game, game->tex_NO);
	if (game->tex_SO)
		free_tex(game, game->tex_SO);
	if (game->tex_WE)
		free_tex(game, game->tex_WE);
	if (game->tex_EA)
		free_tex(game, game->tex_EA);
	free(game);
	return (0);
}
