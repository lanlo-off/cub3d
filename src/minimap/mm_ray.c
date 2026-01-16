/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:52:36 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 10:13:04 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	mm_draw_ray_floor(t_img *img, t_player *player, t_ray ray)
{
	int	px_player;
	int	py_player;
	int	px_hit;
	int	py_hit;
	int	x;
	int y;
	int	steps;
	int	i;

	px_player = player->x * TILE_SIZE;
	py_player = player->y * TILE_SIZE;
	px_hit = ray.hit_x * TILE_SIZE;
	py_hit = ray.hit_y * TILE_SIZE;
	steps = fmax(abs(px_hit - px_player), abs(py_hit - py_player));
	if (steps == 0)
		return ;
	i = 0;
	while (i <= steps)
	{
		x = px_player + (px_hit - px_player) * i / steps;
		y = py_player + (py_hit - py_player) * i / steps;
		put_pixel(img, x, y, 0xFFFFFF);
		i++;
	}
}

bool	mm_print_ray_img(t_game *game, t_map *map, t_player *player, int nb_ray)
{
	t_ray	ray;

	ray.index = nb_ray;
	mm_get_ray_values(&ray, player);
	mm_calculate_hitpoint(&ray, map, player);
	mm_draw_ray_floor(game->img, player, ray);//before the wall
	return (true);
}
