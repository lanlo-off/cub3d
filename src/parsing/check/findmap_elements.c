/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findmap_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:50:12 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/19 15:10:53 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool	find_tex2(t_game *g, char *line)
{
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (g->tex_SO->flag < 1)
			g->tex_SO->path = ft_strtrim(skip_spaces(line + 3), " \t\n");
		g->tex_SO->flag++;
	}
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (g->tex_WE->flag < 1)
			g->tex_WE->path = ft_strtrim(skip_spaces(line + 3), " \t\n");
		g->tex_WE->flag++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (g->tex_EA->flag < 1)
			g->tex_EA->path = ft_strtrim(skip_spaces(line + 3), " \t\n");
		g->tex_EA->flag++;
	}
	return (true);
}

static bool	find_tex(t_game *g)
{
	int		i;
	char	*line;

	i = 0;
	while (g->map->raw[i])
	{
		line = skip_spaces(g->map->raw[i]);
		i++;
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			if (g->tex_NO->flag < 1)
				g->tex_NO->path = ft_strtrim(skip_spaces(line + 3), " \t\n");
			g->tex_NO->flag++;
		}
		else if (!find_tex2(g, line))
			return (false);
	}
	if (g->tex_NO->flag == 1 && g->tex_SO->flag == 1 && \
			g->tex_WE->flag == 1 && g->tex_EA->flag == 1)
		return (true);
	return (false);
}

static bool	find_color2(t_game *g, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (g->c_color->flag < 1)
			g->c_color->line = ft_strtrim(skip_spaces(line + 2), " \t\n");
		g->c_color->flag++;
	}
	return (true);
}

static bool	find_color(t_game *g)
{
	int		i;
	char	*line;

	i = 0;
	while (g->map->raw[i])
	{
		while (g->map->raw[i] && empty_line(g->map->raw[i]))
			i++;
		if (!g->map->raw[i])
			break ;
		line = skip_spaces(g->map->raw[i++]);
		if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (g->f_color->flag < 1)
				g->f_color->line = ft_strtrim(skip_spaces(line + 2), " \t\n");
			g->f_color->flag++;
		}
		else if (!find_color2(g, line))
			return (false);
	}
	if (g->f_color->flag == 1 && g->c_color->flag == 1)
		return (true);
	return (false);
}

bool	findmap_elements(t_game *game)
{
	if (!fill_raw(game))
		return (ft_error(game, ERR_MALLOC), false);
	if (!no_invalid_char_found(game))
		return (ft_error(game, ERR_MAP_CHARS), false);
	if (!find_tex(game))
		return (ft_error(game, ERR_TEX_NUMBER), false);
	if (!find_color(game))
		return (ft_error(game, ERR_COLOR_NUMBER), false);
	if (!find_map(game))
		return (ft_error(game, ERR_MAP_FIND), false);
	if (!fill_grid(game))
		return (ft_error(game, ERR_MALLOC), false);
	if (!check_player_pos(game->map))
		return (ft_error(game, ERR_PLAYER_NUMBER), false);
	return (true);
}
