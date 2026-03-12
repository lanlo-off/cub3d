/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findmap_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:50:12 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/12 19:04:11 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool find_tex2(t_game *g, char *line)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		g->tex_WE->path = ft_strtrim(skip_spaces(line + 3), " \t\n");
		g->tex_WE->flag++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		g->tex_EA->path = ft_strtrim(skip_spaces(line + 3), " \t\n");
		g->tex_EA->flag++;
	}
	return (true);
}

static bool find_tex(t_game *g)
{
	int     i;
	char    *line;

	i = 0;
	while (g->map->raw[i])
	{
		line = skip_spaces(g->map->raw[i]);
		i++;
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			g->tex_NO->path = ft_strtrim(skip_spaces(line + 3), " \t\n");
			g->tex_NO->flag++;
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			g->tex_SO->path = ft_strtrim(skip_spaces(line + 3), " \t\n");
			g->tex_SO->flag++;            
		}
		else if (!find_tex2(g, line))
			return (false);
	}
	if (g->tex_NO->flag == 1 && g->tex_SO->flag == 1 && \
		g->tex_WE->flag == 1 && g->tex_EA->flag == 1)
		return (true);
	return (false);
}

static bool find_color(t_game *g)
{
	int     i;
	char    *line;

	i = 0;
	while (g->map->raw[i])
	{
		while (g->map->raw[i] && empty_line(g->map->raw[i]))
			i++;
		if (!g->map->raw[i])
			break;
		line = skip_spaces(g->map->raw[i++]);
		if (ft_strncmp(line, "F ", 2) == 0)
		{
			g->f_color->line = ft_strtrim(skip_spaces(line + 2), " \t\n");
			g->f_color->flag++;
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			g->c_color->line = ft_strtrim(skip_spaces(line + 2), " \t\n");
			g->c_color->flag++;
		}
	}
	if (g->f_color->flag == 1 && g->c_color->flag == 1)
		return (true);
	return (false);
}

bool    find_map(t_game *g)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (g->map->raw[i])
	{
		// printf("raw[%d] pointer value is %s", i, g->map->raw[i]);
		while (g->map->raw[i] && valid_line(" 01NSEW", g->map->raw[i]))
		{
			// printf("raw[%d] pointer value is %s", i, g->map->raw[i]);
			if (valid_line(" 1", g->map->raw[i]) && (g->map->start < 0))
				g->map->start = i;
			len = ft_strlen(g->map->raw[i]);
			if (len > g->map->max)
				g->map->max = len;
			i++;
		}
		if (i > 0 && valid_line(" 1", g->map->raw[i - 1]) && (g->map->end < 0) \
		&& (g->map->start > 0))
		{
			// printf("map end is %d\n", i-1);
			g->map->end = i - 1;
			break ;
		}	
		printf("%d\n", i);
		i++;
	}
	// printf("Sortie de boucle");
	if (((g->map->end - g->map->start) > 3) && g->map->end > 0 \
		&& (g->map->start > 0))
		return (true);
	return (false);
}

bool    findmap_elements(t_game *game)
{
	if (!fill_raw(game))
		return (false);
	printf(":::fillraw\n");
	if (!find_tex(game))
		return (printf(":::findtex\n"), false);
	printf(":::findtex\n");
	if (!find_color(game))
		return (false);
	printf(":::findcolor\n");
	if (!find_map(game))
		return (printf(":::findmap\n"), false);
	printf(":::findmap\n");
	if (!fill_grid(game))
		return (false);
	printf(":::fillgrid\n");
	if (!check_player_pos(game->map))
		return (ft_error(game, ERR_PLAYER_NUMBER), false);
	printf(":::playerpos\n");
	return (true);
}
