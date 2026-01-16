/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:48:30 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 13:08:57 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	init_textures(t_game *g)
{
	g->tex_NO = ft_calloc(1, sizeof(t_tex));
	if (!g->tex_NO)
		return (false);
	g->tex_SO = ft_calloc(1, sizeof(t_tex));
	if (!g->tex_SO)
		return (free(g->tex_NO), false);
	g->tex_WE = ft_calloc(1, sizeof(t_tex));
	if (!g->tex_WE)
		return (free(g->tex_NO), free(g->tex_SO), false);
	g->tex_EA = ft_calloc(1, sizeof(t_tex));
	if (!g->tex_EA)
		return (free(g->tex_NO), free(g->tex_SO), free(g->tex_WE), false);
	return (true);
}

static void	is_player2(char c, t_player *player)
{
	if (c == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		// player->plane_x = 0;
		// player->plane_y = 0.66;
	}
	if (c == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		// player->plane_x = 0;
		// player->plane_y = -0.66;
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
		// player->plane_x = 0.66;
		// player->plane_y = 0;
	}
	if (c == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		// player->plane_x = -0.66;
		// player->plane_y = 0;
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
