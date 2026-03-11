/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closemap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:57:39 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/11 08:49:20 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char **copy_map(char **map, int height)
{
	char **copy;
	int i;

	copy = malloc(sizeof(char *) * (height + 1));
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

bool flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (false);
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return (false);
	if (map[y][x] == ' ')
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (true);
	map[y][x] = 'F';
	if (flood_fill(map, x + 1, y) == false)
		return (false);
	if (flood_fill(map, x - 1, y) == false)
		return (false);
	if (flood_fill(map, x, y + 1) == false)
		return (false);
	if (flood_fill(map, x, y - 1) == false)
		return (false);
	return (true);
}

int find_zero(char **map, int *x, int *y)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

bool check_map_closed(t_map *map)
{
	char **copy;
    int x;
	int y;
    int p_x;
    int p_y;

    p_x = map->p_pos[0];
    p_y = map->p_pos[1];
	copy = copy_map(map->grid, map->end - map->start);
	if (flood_fill(copy, p_x, p_y) == false)
		return (free_tab(copy), false);
    while (find_zero(copy, &x, &y))
	{
		if (flood_fill(copy, x, y) == false)
			return (false);
	}
	free_tab(copy);
	return (true);
}
