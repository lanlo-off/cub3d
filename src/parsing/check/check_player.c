/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:28:38 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/11 08:50:08 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool    check_player_pos(t_map *map)
{
    int x;
    int y;
    
    x = 0;
    y = 0;
    map->p_pos = malloc(sizeof(int) * 2);
	if (!map->p_pos)
		return (false);
    while (map->grid[y])
    {
        x = 0;
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
