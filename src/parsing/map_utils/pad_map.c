/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:13:24 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/11 09:30:14 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	**mallocfile(t_game *g)
{
	char	**res;
	int	    i;
    int     height;

    height = g->map->end - g->map->start;
	res = malloc(sizeof(char *) * (height + 1));
	if (!res)
			ft_error(g, ERR_MALLOC);
	i = 0;
	while (i < height)
	{
		res[i] = malloc(sizeof(char) * (g->map->max + 1));
		if (!res[i])
		{
			while (--i >= 0)
				free(res[i]);
			(free(res), ft_error(g, ERR_MALLOC));
		}
		i++;
	}
    res[i] = NULL;
	return (res);
}

void	pad_line(char *mapped_line, char *raw_line, int max_len)
{
	int		i;

	i = 0;
	while (raw_line && raw_line[i] && i < max_len)
    {
        if (raw_line[i] == ' ')
		    mapped_line[i] = 'a';
        else
            mapped_line[i] = raw_line[i];
        i++;
    }
	while (i < max_len)
		mapped_line[i++] = 'a';
	mapped_line[i] = '\0';
}

bool    fill_grid(t_game *g)
{
    int i;
    int raw_i;

    g->map->grid = mallocfile(g);
	if (!g->map->grid)
		return (false);
    i = 0;
    raw_i = g->map->start;
    while (i < (g->map->end - g->map->start))
    {
        pad_line(g->map->grid[i], g->map->raw[raw_i], g->map->max);
        i++;
        raw_i++;
    }
    return (true);
}
