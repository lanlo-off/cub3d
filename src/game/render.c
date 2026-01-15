/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:35:35 by llechert          #+#    #+#             */
/*   Updated: 2026/01/15 20:01:27 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_wall(t_game *g, t_img *img, t_ray ray)
{
	int	y;
	int	color;

	y = ray.wall_start;
	while (y < ray.wall_start && y < WIN_HEIGHT / 2)
	{
		color = get_color_from_xpm(ray.index, y, ray.wall_texture);
		put_pixel(img, ray.index, y, color);
		y++;
	}
}

static void	draw_floor(t_game *g, t_img *img, t_ray ray)
{
	int	y;
	int	color;

	y = ray.wall_end;//car en bas de la fenetre = y est au max
	color = rgb_to_int(g->floor_color);
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
	color = rgb_to_int(g->ceiling_color);
	while (y <= WIN_HEIGHT / 2 && y < ray.wall_start)
	{
		put_pixel(img, ray.index, y, color);
		y++;
	}
}

void render(t_game *game, t_mlx *mlx, t_img *img)
{
	int	nb_ray;
	t_ray	ray;

	nb_ray = 0;
	reset_background(img);
	while (nb_ray < WIN_WIDTH)//On veut faire 1 rayon par colonne de la fenetre
	{
		ray.index = nb_ray;
		get_ray_values(&ray, game->player);//init les valeurs du ray en fonction du joueur et de son index
		calculate_hitpoint(game, &ray, game->map, game->player);//calcule tout sur le mur
		draw_floor(game, game->img, ray);
		draw_wall(game, game->img, ray);
		draw_ceiling(game, game->img, ray);
		nb_ray++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
	// mlx_destroy_image(mlx->mlx_ptr, img->img_ptr);
}