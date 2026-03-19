/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:50:12 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/19 15:10:21 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	findstart(t_game *g, int i)
{
	int	len;

	while (g->map->raw[i] && valid_line(" 01NSEW", g->map->raw[i]))
	{
		len = 0;
		if (valid_line(" 1", g->map->raw[i]) && (g->map->start < 0))
			g->map->start = i;
		len = ft_strlen(g->map->raw[i]);
		if (len > g->map->max)
			g->map->max = len;
		i++;
	}
	return (i);
}

bool	find_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->map->raw[i])
	{
		i = findstart(g, i);
		if (i > 0 && valid_line(" 1", g->map->raw[i - 1]) && (g->map->end < 0) \
				&& (g->map->start > 0))
		{
			g->map->end = i - 1;
			break ;
		}
		i++;
	}
	if (((g->map->end - g->map->start) > 3) && g->map->end > 0 \
			&& (g->map->start > 0))
		return (true);
	return (false);
}
