/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:57:54 by llechert          #+#    #+#             */
/*   Updated: 2026/01/07 18:54:39 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_player(int i, int j, char c, t_player *player)
{
	if (c == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (c == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (c == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (c == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else
		return (false);
	player->x = i + 0.5;
	player->y = j + 0.5;
	return (true);
}

