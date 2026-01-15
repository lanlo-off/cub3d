/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:35:35 by llechert          #+#    #+#             */
/*   Updated: 2026/01/15 18:30:48 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void set_color(t_color *color, char *name)
{
	if (!color || !name)
		return;
	if (ft_strcmp(name, "blue") == 0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 255;
	}
	else if (ft_strcmp(name, "white") == 0)
	{
		color->r = 255;
		color->g = 255;
		color->b = 255;
	}
	else if (ft_strcmp(name, "green") == 0)
	{
		color->r = 0;
		color->g = 255;
		color->b = 0;
	}
	else if (ft_strcmp(name, "black") == 0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else if (ft_strcmp(name, "red") == 0)
	{
		color->r = 255;
		color->g = 0;
		color->b = 0;
	}
}

void print_map(t_game *game, t_mlx *mlx, t_img *img)
{
	int	nb_ray;
	t_ray	*ray;

	nb_ray = 0;
	reset_background(img);
	while (nb_ray < WIN_WIDTH)//On veut faire 1 rayon par colonne de la fenetre
	{
		ray->index = nb_ray;
		get_ray_values(ray, game->player);//init les valeurs du ray en fonction du joueur et de son index
		calculate_hitpoint(ray, game->map, game->player);//calcule la zone de rencontre du mur
		print_floor(game, game->player, ray);
		print_wall(game, game->player, ray);
		print_ceiling(game, game->player, ray);
		nb_ray++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
	// mlx_destroy_image(mlx->mlx_ptr, img->img_ptr);
}