/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:24:33 by llechert          #+#    #+#             */
/*   Updated: 2026/01/09 18:22:43 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_img(t_game *game, void *img, int i, int j)
{
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, img,
		game->tile_size * j, game->tile_size * i);
}

void put_pixel(t_img *img, int x, int y, int color)//full IA
{
	char *dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->address + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
