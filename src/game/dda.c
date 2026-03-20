/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:20:14 by llechert          #+#    #+#             */
/*   Updated: 2026/03/19 15:30:49 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief 6- On fait avancer le ray jusqu'au mur, 
 * en progressant frontiere par frontiere
 * 
 * 
 * @param ray 
 * @param map 
 */
static void	advance_to_wall(t_ray *ray, t_map *map)
{
	while (ray->map_x >= 0 && ray->map_x <= map->width
		&& ray->map_y >= 0 && ray->map_y <= map->height
		&& map->grid[ray->map_y][ray->map_x] != '1')
	{
		if (!map->grid || !map->grid[ray->map_y])
		{
			printf("ERROR: map->grid corruption at y=%d\n", ray->map_y);
			break ;
		}
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->frontier_type = VERTICAL;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->frontier_type = HORIZONTAL;
		}
	}
}

/**
 * @brief 7- On peut deduire la wall_texture et la perp distance
 * 8- Calcule de l'emplacement exact du hitpoint
 * 9- Calcul du positionnement du mur sur ce rayon (debut, hauteur, fin)
 * 
 * @param g 
 * @param ray 
 * @param map 
 * @param player 
 * @return true 
 * @return false 
 */
bool	calculate_hitpoint(t_game *g, t_ray *ray, t_map *map, t_player *player)
{
	advance_to_wall(ray, map);
	if (ray->frontier_type == VERTICAL)
	{
		if (ray->step_x == 1)
			ray->wall_texture = g->tex_we;
		else
			ray->wall_texture = g->tex_ea;
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;
	}
	else
	{
		if (ray->step_y == 1)
			ray->wall_texture = g->tex_no;
		else
			ray->wall_texture = g->tex_so;
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
	}
	if (ray->perp_dist < EPSILON)
		ray->perp_dist = EPSILON;
	ray->hit_x = player->x + ray->dir_x * ray->perp_dist;
	ray->hit_y = player->y + ray->dir_y * ray->perp_dist;
	ray->wall_height = (int)(WIN_HEIGHT / ray->perp_dist);
	ray->wall_start = -ray->wall_height / 2 + WIN_HEIGHT / 2;
	ray->wall_end = ray->wall_height / 2 + WIN_HEIGHT / 2;
	return (true);
}

/**
 * @brief 0- Positionnement du rayon dans le plan de la camera
 * 1- Orientation du rayon = player car pour l'instant 
 * on prend uniquement le rayon central
 * 2- Deduction du sens
 * 3- position d'origine du rayon 
 * = celle du joueur (changera en cour de dessin peut etre)
 * 4- calcul de la distance pour parcourir une case entiere
 * 5- deduction de la distance pour la case en cours de traversee :
 * 
 * @param ray 
 * @param player 
 */
void	get_ray_values(t_ray *ray, t_player *player)
{
	double	camera_x;

	camera_x = 2.0 * ray->index / (double)WIN_WIDTH - 1.0;
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->step_x = ((ray->dir_x >= 0) - (ray->dir_x < 0));
	ray->step_y = ((ray->dir_y >= 0) - (ray->dir_y < 0));
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	if (fabs(ray->dir_x) < EPSILON)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (fabs(ray->dir_y) < EPSILON)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	ray->side_dist_x = ray->delta_dist_x
		* fabs((player->x - ray->map_x - (ray->step_x == 1)));
	ray->side_dist_y = ray->delta_dist_y
		* fabs((player->y - ray->map_y - (ray->step_y == 1)));
}
