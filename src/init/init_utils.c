/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:48:30 by llechert          #+#    #+#             */
/*   Updated: 2026/03/12 19:51:44 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	init_textures(t_game *g)
{
	g->tex_no = ft_calloc(1, sizeof(t_tex));
	if (!g->tex_no)
		return (false);
	g->tex_so = ft_calloc(1, sizeof(t_tex));
	if (!g->tex_so)
		return (free(g->tex_no), false);
	g->tex_we = ft_calloc(1, sizeof(t_tex));
	if (!g->tex_we)
		return (free(g->tex_no), free(g->tex_so), false);
	g->tex_ea = ft_calloc(1, sizeof(t_tex));
	if (!g->tex_ea)
		return (free(g->tex_no), free(g->tex_so), free(g->tex_we), false);
	g->f_color = ft_calloc(1, sizeof(t_color));
	if (!g->f_color)
		return (free(g->tex_no), free(g->tex_so), free(g->tex_we), \
			free(g->tex_ea), false);
	g->c_color = ft_calloc(1, sizeof(t_color));
	if (!g->c_color)
		return (free(g->tex_no), free(g->tex_so), free(g->tex_we), \
			free(g->tex_ea), free(g->f_color), false);
	return (true);
}

bool	init_map(t_game *g)
{
	g->map = ft_calloc(1, sizeof(t_map));
	if (!g->map)
		return (false);
	g->map->start = -1;
	g->map->end = -1;
	g->map->p_flag = 0;
	return (true);
}

static void	is_player2(char c, t_player *player)
{
	if (c == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	if (c == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
}

static bool	is_player(int i, int j, char c, t_player *player)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (false);
	if (c == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	if (c == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	is_player2(c, player);
	player->x = j + 0.5;
	player->y = i + 0.5;
	player->plane_x = -player->dir_y * tan(M_PI / 6);
	player->plane_y = player->dir_x * tan(M_PI / 6);
	return (true);
}

bool	get_player_start(char **map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(i, j, map[i][j], player))
			{
				map[i][j] = '0';
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}
