/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:13:24 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/09 10:52:34 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	**mallocfile(t_game *g)
{
	char	**res;
	int	    i;
    int     height;

    height = g->map->end - g->map->start;
	res = malloc(sizeof(int *) * height);
	if (!res)
		free_exit(g);
	i = 0;
	while (i < height)
	{
		res[i] = malloc(sizeof(int) * g->map->max + 1);
		if (!res[i])
		{
			while (--i >= 0)
				free(res[i]);
			free(res);
			free_exit(g);
		}
		i++;
	}
	return (res);
}

char	*pad_line(t_map *map)
{
	char	*new;
	int		i;

	i = 0;
	while (map->raw[i] && i < map->max)
    {
        if (map->raw[i] == " ")
		    new[i] = 'a';
        else
		    new[i] = map->raw[i];
        i++;
    }
	while (i < map->max)
		new[i++] = 'a';
	new[i] = '\0';
	return (new);
}

bool    fill_grid(t_game *g)
{
    int i;

    g->map->grid = mallocfile(g);
	if (!g->map->grid)
		return (false, free_exit(g));
    i = 0;
    while (g->map->grid[i])
    {
        g->map->grid[i] = pad_line(g->map);
        i++;
    }
    return (true);
}
