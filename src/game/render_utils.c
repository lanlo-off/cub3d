/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:52:36 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 11:38:07 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/**
 * @brief Get the color from xpm object
 * 
 * y * line_len : descendre de y lignes
 *  x * (bpp / 8) : avancer de x pixels dans la ligne
 * 
 * (unsigned int *) : interpréter les 4 octets comme un entier couleur 0xRRGGBB
 * 
 * @param x 
 * @param y 
 * @param tex 
 * @return int 
 */
int	get_color_from_xpm(int x, int y, t_tex *tex)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

/**
 * @brief Transforme un rgb en int en partant du principe que 
 * une couleur devient un int qui s'ecrit (0x00RRGGBB)
 * 
 * Un int fait 32 bits :
[00000000][RRRRRRRR][GGGGGGGG][BBBBBBBB]
    8 bits     8         8         8
r << 16 place le rouge dans l’octet 2
g << 8 place le vert dans l’octet 1
b reste dans l’octet 0

 * @param color 
 * @return int 
 */
int	rgb_to_int(t_color *color)
{
	int	res;

	res = (color->r << 16) | (color->g << 8) | color->b;
	return (res);
}
