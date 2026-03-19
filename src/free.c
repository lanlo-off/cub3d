/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:11:42 by llechert          #+#    #+#             */
/*   Updated: 2026/03/19 15:00:50 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_img(t_game *game, t_img *img)
{
	mlx_destroy_image(game->mlx->mlx_ptr, img->img_ptr);
	free(img);
}

void	free_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	if (mlx->mlx_ptr)
		free(mlx->mlx_ptr);
	free(mlx);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->raw)
		free_tab(map->raw);
	if (map->grid)
		free_tab(map->grid);
	if (map->p_pos)
		free(map->p_pos);
	free(map);
}

void	free_tex(t_game *g, t_tex *texture)
{
	if (!texture)
		return ;
	if (g && g->mlx && texture->img)
		mlx_destroy_image(g->mlx->mlx_ptr, texture->img);
	if (texture->path)
		free(texture->path);
	free(texture);
}
