/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:28:38 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/10 08:55:35 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool    check_player_pos(t_map *map)
{
    int x;
    int y;

    map->p_pos = malloc(sizeof(int) * 2);
	if (!map->p_pos)
		return (false);
    while (map->grid[y])
    {
        while (map->grid[y][x])
        {
            if (ft_strchr("NSWE", map->grid[y][x]))
            {
                map->p_pos[0] = x;
                map->p_pos[1] = y;
                return (true);
            }
            x++;
        }
        y++;
    }
    return (false);
}
