/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:35:35 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 11:56:12 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_wall(t_img *img, t_ray ray, t_player *player)
{
	int	y;
	int	color;
	double	wall_x;
	int		texture_x;
	int		texture_y;

	if (ray.frontier_type == VERTICAL)
		wall_x = player->y + ray.perp_dist * ray.dir_y;
	else
		wall_x = player->x + ray.perp_dist * ray.dir_x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * (double)(ray.wall_texture->width));
	if (ray.frontier_type == VERTICAL && ray.dir_x > 0)
		texture_x = ray.wall_texture->width - texture_x - 1;
	if (ray.frontier_type == HORIZONTAL && ray.dir_y < 0)
		texture_x = ray.wall_texture->width - texture_x - 1;
	y = ray.wall_start;
	// printf("Draw_wall : index = [%d], y = [%d], wall-start = [%d], wall-end = [%d]\n", ray.index, y, ray.wall_start, ray.wall_end);
	while (y <= ray.wall_end && y < WIN_HEIGHT)
	{
		texture_y = ((y - ray.wall_start) * ray.wall_texture->height) / ray.wall_height;
		color = get_color_from_xpm(texture_x, texture_y, ray.wall_texture);
		put_pixel(img, ray.index, y, color);
		y++;
	}
}

static void	draw_floor(t_game *g, t_img *img, t_ray ray)
{
	int	y;
	int	color;

	y = ray.wall_end + 1;//car en bas de la fenetre = y est au max
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
	while (y < ray.wall_start && y <= WIN_HEIGHT / 2)
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
	// reset_background(img);
	while (nb_ray < WIN_WIDTH)//On veut faire 1 rayon par colonne de la fenetre
	{
		ray.index = nb_ray;
		get_ray_values(&ray, game->player);//init les valeurs du ray en fonction du joueur et de son index
		calculate_hitpoint(game, &ray, game->map, game->player);//calcule tout sur le mur
		draw_ceiling(game, game->img, ray);
		draw_wall(game->img, ray, game->player);
		draw_floor(game, game->img, ray);
		nb_ray++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
	// mlx_destroy_image(mlx->mlx_ptr, img->img_ptr);
}