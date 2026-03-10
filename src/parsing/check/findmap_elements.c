/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findmap_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:50:12 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/10 09:03:06 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void find_tex2(t_game *g, char *line)
{
    if (ft_strncmp(line, "WE ", 3))
    {
        g->tex_WE->path = skip_spaces(line + 3);
        g->tex_WE->flag++;
    }
    if (ft_strncmp(line, "EA ", 3))
    {
        g->tex_EA->path = skip_spaces(line + 3);
        g->tex_EA->flag++;
    }
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
        if (ft_strncmp(line, "NO ", 3))
        {
            g->tex_NO->path = skip_spaces(line + 3);
            g->tex_NO->flag++;
        }
        if (ft_strncmp(line, "SO ", 3))
        {
            g->tex_SO->path = skip_spaces(line + 3);
            g->tex_SO->flag++;            
        }
       find_tex2(g, line);
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
        while (empty_line(g->map->raw[i]))
            i++;
        line = skip_spaces(g->map->raw[i]);
        i++;
        if (ft_strncmp(line, "F ", 2))
        {
            g->f_color->line = skip_spaces(line + 2);
            g->f_color->flag++;
        }
        if (ft_strncmp(line, "C ", 2))
        {
            g->c_color->line = skip_spaces(line + 2);
            g->c_color->flag++;
        }
    }
    if (g->f_color == 1 && g->c_color == 1)
        return (true);
    return (false);
}

bool    find_map(t_game *g)
{
    int i;
    int len;

    i = 0;
    while (g->map->raw[i])
    {
        while (valid_line(" 01NSEW", g->map->raw[i]))
        {
            if (valid_line(" 1", g->map->raw[i]) && (g->map->start < 0))
                g->map->start = i;
            len = ft_strlen(g->map->raw[i]);
            if (len > g->map->max)
			    g->map->max = len;
            i++;
        }
        if (valid_line(" 1", g->map->raw[i - 1]) && (g->map->end < 0) \
        && (g->map->start > 0))
            g->map->end = i;
        i++;
    }
    if (((g->map->end - g->map->start) > 3) && g->map->end > 0 \
        && (g->map->start > 0))
        return (true);
    return (false);
}

bool    findmap_elements(t_game *game)
{
    if (!fill_raw(game))
        return (false);
    if (!find_tex(game))
        return (false);
    if (!find_color(game))
        return (false);
    if (!find_map(game))
        return (false);
    if (!check_player_pos(game->map))
        return (false);
    return (true);
}
