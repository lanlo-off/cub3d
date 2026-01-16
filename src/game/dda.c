/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:20:14 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 13:39:19 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

bool	calculate_hitpoint(t_game *g, t_ray *ray, t_map *map, t_player *player)
{
	advance_to_wall(ray, map);
	//7- On peut deduire la wall_texture et la perp distance
	if (ray->frontier_type == VERTICAL)//on est donc sur EST ou OUEST
	{
		if (ray->step_x == 1)
			ray->wall_texture = g->tex_WE;
		else
			ray->wall_texture = g->tex_EA;
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;//Calcule de la perp_dist (mais ce n'est pas une correction du fish eye)
		// ray->perp_dist = (ray->map_x - player->x + ( 1 - ray->step_x) / 2) / ray->dir_x;
	}
	else
	{
		if (ray->step_y == 1)
			ray->wall_texture = g->tex_NO;
		else
			ray->wall_texture = g->tex_SO;
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
		// ray->perp_dist = (ray->map_y - player->y + ( 1 - ray->step_y) / 2) / ray->dir_y;
	}
	
	/*pour verifier une theorie, sinon remettre au debut du 9 ou retirer*/
	if (ray->perp_dist < EPSILON)
		ray->perp_dist = EPSILON;//pour eviter la division par 0 ensuite si jamais on a un pb de parsing/de traversage de mur

	//8- Calcule de l'emplacement exact du hitpoint
	ray->hit_x = player->x + ray->dir_x * ray->perp_dist;
	ray->hit_y = player->y + ray->dir_y * ray->perp_dist;

	//9- Calcul du positionnement du mur sur ce rayon (debut, hauteur, fin)
	ray->wall_height = (int)(WIN_HEIGHT / ray->perp_dist);
	ray->wall_start = -ray->wall_height / 2 + WIN_HEIGHT / 2;//car le mur est centre en hauteur
	ray->wall_end = ray->wall_height / 2 + WIN_HEIGHT / 2;

	/*Ne surtout pas rajouter ce qu'il y a en dessous sinon ca fait une sorte de fish eye ->on met les securites dans le draw wall deja*/
	// if (ray->wall_start < 0)
	// 	ray->wall_start = 0;
	// if (ray->wall_end >= WIN_HEIGHT) 
	// 	ray->wall_end = WIN_HEIGHT - 1;
	return (true);
}


void	get_ray_values(t_ray *ray, t_player *player)
{
	double	camera_x;

	/*positionnement du rayon dans le plan de la camera*/
	camera_x = 2.0 * ray->index / (double)WIN_WIDTH - 1.0;
	/*1- Orientation du rayon = player car pour l'instant on prend uniquement le rayon central*/
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	
	/*2- Deduction du sens*/
	ray->step_x = ((ray->dir_x >= 0) - (ray->dir_x < 0));
	ray->step_y = ((ray->dir_y >= 0) - (ray->dir_y < 0));
	
	/*3- position d'origine du rayon = celle du joueur (changera en cour de dessin peut etre)*/
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	
	/*4- calcul de la distance pour parcourir une case entiere*/
	if (fabs(ray->dir_x) < EPSILON)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0/ray->dir_x);
	if (fabs(ray->dir_y) < EPSILON)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0/ray->dir_y);

	//5- deduction de la distance pour la case en cours de traversee : on peut ecrire sans if avec
	ray->side_dist_x = ray->delta_dist_x * fabs((player->x - ray->map_x - (ray->step_x == 1)));
	ray->side_dist_y = ray->delta_dist_y * fabs((player->y - ray->map_y - (ray->step_y == 1)));
}
