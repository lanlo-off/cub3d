/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:59:58 by llechert          #+#    #+#             */
/*   Updated: 2026/03/19 15:02:27 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Doit pouvoir tout free
 * Voir si game->mlx, game->player etc... 
 * doivent etre free ou si ce sont des coquilles
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

void	free_game2(t_game *game)
{
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

void	free_game(t_game *game)
{
	if (!game)
		return ;
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
	free_game2(game);
}
