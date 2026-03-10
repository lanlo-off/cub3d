/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:57:21 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/06 12:27:42 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool check_color(t_game *game, t_color *color)
{
    char **rgb;
    char *values;

    values = skip_identifier(color->line);
    rgb = ft_split(values, ',');
    if (!rgb || count_tab(rgb) != 3)
        error("Invalid RGB format");
    color->r = check_rgb_value(rgb[0]);
    color->g = check_rgb_value(rgb[1]);
    color->b = check_rgb_value(rgb[2]);
    if (color->r > 0 && color->g > 0 && color->b > 0)
        return (true, free_tab(rgb));
    return (free_tab(rgb), false);
}

static bool check_path(t_game *game)
{
    if (!valid_path(game->tex_EA->path))
        return (false);
    if (!valid_path(game->tex_NO->path))
        return (false);
    if (!valid_path(game->tex_SO->path))
        return (false);
    if (!valid_path(game->tex_WE->path))
        return (false);
    return (true);
}

bool    check_texture(t_game *game)
{
	if (!check_path(game))
		return (false);
    if (!check_color(game, game->f_color) || !check_color(game, game->c_color))
        return (false);
    return (true);
}