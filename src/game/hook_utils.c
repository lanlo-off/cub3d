/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:19:07 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 11:00:37 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void	rotate(t_player *player, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir_x * sin(rot) + player->dir_y * cos(rot);
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane_x * sin(rot) + player->plane_y * cos(rot);
}

bool	is_in_map(double x, int value)
{
	return ((int)x >= 0 && (int)x < value);
}

// /**
//  * @brief Permet d'avancer ou de reculer selon qu'on passe + ou - MOV_SPEED en argument
//  * 
//  * @param map 
//  * @param player 
//  * @param ms + MOV_SPEED si on hook un W (avance) ; -MOV_SPEED si c'est un S (recule)
//  */
// void	move_in_line(char **grid, t_player *player, double ms)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = player->x + player->dir_x * ms;
// 	new_y = player->y + player->dir_y * ms;
// 	if (grid[(int)new_y][(int)player->x] == '0')
// 		player->y = new_y;
// 	if (grid[(int)player->y][(int)new_x] == '0')
// 		player->x = new_x;
// }
// /**
//  * @brief permet de se deplacer lateralement
//  * 
//  * @param grid 
//  * @param player 
//  * @param ms + MOV_SPEED si vers la droite (hook D) ; - MOV_SPEED si vers la gauche (hook A)
//  */
// void	strafe(char **grid, t_player *player, double ms)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = player->x + player->plane_x * ms;
// 	new_y = player->y + player->plane_y * ms;
// 	if (grid[(int)new_y][(int)player->x] == '0')
// 		player->y = new_y;
// 	if (grid[(int)player->y][(int)new_x] == '0')
// 		player->x = new_x;
// }