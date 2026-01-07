/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:52:36 by llechert          #+#    #+#             */
/*   Updated: 2026/01/07 19:08:18 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	print_ray(t_map *map, t_player *player, char *img_data)
{
	t_ray	ray;

	/*Orientation du rayon = player car pour l'instant on prend uniquement le rayon central*/
	ray.dir_x = player->dir_x;
	ray.dir_y = player->dir_y;
	
	/*position d'origine du rayon = celle du joueur*/
	ray.map_x = (int)player->x;
	ray.map_y = (int)player->y;
	
	/*calcul de la longueur du rayon = quand on rencontre un mur*/
	
}