/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:20:14 by llechert          #+#    #+#             */
/*   Updated: 2026/01/14 18:34:19 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_ray_values(t_ray *ray, t_player *player)
{
	double	camera_x;

	/*positionnement du rayon dans le plan de la camera*/
	camera_x = 2.0 * ray->index / (MM_NB_RAY - 1) - 1.0;
	/*1- Orientation du rayon = player car pour l'instant on prend uniquement le rayon central*/
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	
	/*2- Deduction du sens*/
	ray->step_x = ((ray->dir_x >= 0) - (ray->dir_x < 0));
	ray->step_y = ((ray->dir_y >= 0) - (ray->dir_y < 0));
	/*Soit en plus explicite 
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else if (ray->dir_x >= 0)
		ray->step_x = 1; on ne l'utilisera pas si dirx == 0 donc ok*/
	
	/*3- position d'origine du rayon = celle du joueur (changera en cour de dessin peut etre)*/
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	
	/*4- calcul de la distance pour parcourir une case entiere*/
	if (fabs(ray->dir_x) < EPSILON)
		ray->delta_dist_x = 1e30;//pour eviter une division par un nombre trop petit ou par 0
	else
		ray->delta_dist_x = fabs(1.0/ray->dir_x);//car dirx = cos de l'angle
	if (fabs(ray->dir_y) < EPSILON)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0/ray->dir_y);//car diry = sin de l'angle

	//5- deduction de la distance pour la case en cours de traversee : on peut ecrire sans if avec
	ray->side_dist_x = ray->delta_dist_x * fabs((player->x - ray->map_x - (ray->step_x == 1)));
	ray->side_dist_y = ray->delta_dist_y * fabs((player->y - ray->map_y - (ray->step_y == 1)));
	/*en plus explicite ca donne
	if (ray->step_x == 1)
		ray->side_dist_x = ray->delta_dist_x * ((ray->map_x + 1) - player->x);
	else
		ray->side_dist_x = ray->delta_dist_x * (player->x - ray->map_x);*/
}

static void	advance_to_wall(t_ray *ray, t_map *map)
{
	//6- On fait avancer le ray jusqu'au mur, en progressant frontiere par frontiere
	while (ray->map_x >= 0 && ray->map_x <= map->width
		&& ray->map_y >= 0 && ray->map_y <= map->height
		&& map->grid[ray->map_y][ray->map_x] != '1')//garanti que ca arrive
	{
		if (ray->side_dist_x < ray->side_dist_y)//on tapera une frontiere verticale en premier (on change de case horizontalement)
		{
			ray->side_dist_x += ray->delta_dist_x;//on remplace pas la valeur on "supprime la frontiere" pour ajouter la distance d'une case entiere comme etant la distance pour aller a la frontiere suivante
			ray->map_x += ray->step_x;//on marque l'avancement dans le sens du pas
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

bool	calculate_hitpoint(t_ray *ray, t_map *map, t_player *player)
{
	advance_to_wall(ray, map);
	//7- On peut deduire la wall_texture et la perp distance
	//ray->wall_texture = ft_calloc(1, sizeof(t_texture));
	//if (!ray->wall_texture)
	//	return (false);
	if (ray->frontier_type == VERTICAL)//on est donc sur EST ou OUEST
	{
	//	if (ray->step_x == 1)
	//		ray->wall_texture = game->textures->west;
	//	else
	//		ray->wall_texture = game->textures->east;
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;//Calcule de la perp_dist (mais ce n'est pas une correction du fish eye)
	}
	else
	{
	//	if (ray->step_y == 1)
	//		ray->wall_texture = game->textures->north;
	//	else
	//		ray->wall_texture = game->textures->south;
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
	}
	
	//8- Calcule de l'emplacement exact du hitpoint
	ray->hit_x = player->x + ray->dir_x * ray->perp_dist;
	ray->hit_y = player->y + ray->dir_y * ray->perp_dist;
	return (true);
}
