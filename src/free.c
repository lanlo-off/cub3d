/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:11:42 by llechert          #+#    #+#             */
/*   Updated: 2026/03/16 18:19:38 by llechert         ###   ########.fr       */
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
	if (mlx->mlx_ptr)//a voir si ce free est necessaire
		free(mlx->mlx_ptr);
	free(mlx);
}

void	free_tab(char **tab)
{
	int i;

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
	free_game(game);
	free(game);
	exit(EXIT_SUCCESS);
}

void free_game(t_game *game)
{
	if (!game)
		return ;
	//if (game->map_path)
	   // free(game->map_path);
	if (game->c_color)
	{
		if (game->c_color->line)
			free(game->c_color->line);
		free(game->c_color);
	}
	if (game->f_color)
	{
		if (game->f_color->line)
			free(game->f_color->line);
		free(game->f_color);
	}
	if (game->img)
		free_img(game, game->img);
	if (game->map)
		free_map(game->map);
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
	if (game->mlx)
		free_mlx(game->mlx);
	if (game->key)
		free(game->key);
}

// void	free_tex_path(t_game *g)
// {
// 	if (!g)
// 		return ;
// 	if (g->tex_NO->path)
// 		free(g->tex_NO->path);
// 	if (g->tex_SO->path)
// 		free(g->tex_SO->path);
// 	if (g->tex_WE->path)
// 		free(g->tex_WE->path);
// 	if (g->tex_EA->path)
// 		free(g->tex_EA->path);
// 	if (g->f_color->line)
// 		free(g->f_color->line);
// 	if (g->c_color->line)
// 		free(g->c_color->line);	
// }
