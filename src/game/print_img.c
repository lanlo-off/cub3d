/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:24:33 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 10:12:53 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Remplit l'image de pixels noirs
 * 
 * @param img 
 */
void	reset_background(t_img *img)
{
	ft_memset(img->address, 0, img->line_len * img->height);
}

/**
 * @brief Pas utilisee pour le moment
 * 
 * @param img 
 * @param color 
 */
void	fill_background(t_img *img, int color)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < img->height)
	{
		while (x < img->width)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

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
