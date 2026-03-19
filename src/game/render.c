/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:35:35 by llechert          #+#    #+#             */
/*   Updated: 2026/03/19 15:22:36 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief 1- On calcule l'endroit precis ou le mur a ete tape (entre 0 et 1)
 * 2- On reprend ce pourcentage et on l'applique
 * a la texture pour recuperer le bon pixel
 * 3- Ce bloc sert a eviter l'inversion de l'impression des textures
 * 4- On demarre au plus grand entre wall_start 
 * et 0 pour eviter de boucler de -1000000 a 0 pour rien
 * 
 * 
 * @param img 
 * @param ray 
 */
static void	draw_wall(t_img *img, t_ray ray)
{
	int		y;
	int		color;
	double	wall_x;
	int		texture_x;
	int		texture_y;

	if (ray.frontier_type == VERTICAL)
		wall_x = ray.hit_y - floor(ray.hit_y);
	else
		wall_x = ray.hit_x - floor(ray.hit_x);
	texture_x = (int)(wall_x * (double)(ray.wall_texture->width));
	if (ray.frontier_type == VERTICAL && ray.dir_x < 0)
		texture_x = ray.wall_texture->width - texture_x - 1;
	if (ray.frontier_type == HORIZONTAL && ray.dir_y > 0)
		texture_x = ray.wall_texture->width - texture_x - 1;
	y = fmax(ray.wall_start, 0);
	while (y <= ray.wall_end && y < WIN_HEIGHT)
	{
		texture_y = ((y - ray.wall_start)
				* ray.wall_texture->height) / ray.wall_height;
		color = get_color_from_xpm(texture_x, texture_y, ray.wall_texture);
		put_pixel(img, ray.index, y, color);
		y++;
	}
}

static void	draw_floor(t_game *g, t_img *img, t_ray ray)
{
	int	y;
	int	color;

	y = ray.wall_end;
	color = rgb_to_int(g->f_color);
	while (y < WIN_HEIGHT && y >= WIN_HEIGHT / 2)
	{
		put_pixel(img, ray.index, y, color);
		y++;
	}
}

static void	draw_ceiling(t_game *g, t_img *img, t_ray ray)
{
	int	y;
	int	color;

	y = 0;
	color = rgb_to_int(g->c_color);
	while (y < ray.wall_start && y <= WIN_HEIGHT / 2)
	{
		put_pixel(img, ray.index, y, color);
		y++;
	}
}

void	render(t_game *game, t_mlx *mlx, t_img *img)
{
	int		nb_ray;
	t_ray	ray;

	nb_ray = 0;
	while (nb_ray < WIN_WIDTH)
	{
		ray.index = nb_ray;
		get_ray_values(&ray, game->player);
		calculate_hitpoint(game, &ray, game->map, game->player);
		draw_ceiling(game, game->img, ray);
		draw_wall(game->img, ray);
		draw_floor(game, game->img, ray);
		nb_ray++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
}
