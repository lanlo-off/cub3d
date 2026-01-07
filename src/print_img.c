/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:24:33 by llechert          #+#    #+#             */
/*   Updated: 2026/01/07 10:30:25 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_img(t_game *game, void *img, int i, int j)
{
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, img,
		game->tile_size * j, game->tile_size * i);
}
