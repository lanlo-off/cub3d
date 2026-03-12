/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:57:21 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/11 08:51:08 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool check_color(t_game *game, t_color *color)
{
    char **rgb;

    rgb = ft_split(color->line, ',');
    printf("::rgb %s\n", rgb[0]);
    printf("::rgb %s\n", rgb[1]);
    printf("::rgb %s\n", rgb[2]);
    if (!rgb || count_tab(rgb) != 3)
    {
        if (rgb)
            free_tab(rgb);
        return (ft_error(game, ERR_COLOR_FORMAT), false);
    }
    color->r = check_rgb_value(rgb[0]);
    color->g = check_rgb_value(rgb[1]);
    color->b = check_rgb_value(rgb[2]);
    if (color->r >= 0 && color->g >= 0 && color->b >= 0)
        return (free_tab(rgb), true);
    free_tab(rgb);
    ft_error(game, ERR_COLOR_RANGE);
    return (false);
}

static bool check_path(t_game *game)
{
    if (!valid_path(game->tex_EA->path))
        return (false);
    printf("::::EA %s\n", game->tex_EA->path);
    if (!valid_path(game->tex_NO->path))
        return (false);
    printf("::::NO %s\n", game->tex_NO->path);
    if (!valid_path(game->tex_SO->path))
        return (false);
    printf("::::SO %s\n", game->tex_SO->path);
    if (!valid_path(game->tex_WE->path))
        return (false);
    printf("::::WE %s\n", game->tex_WE->path);
    return (true);
}

bool    check_texture(t_game *game)
{
	if (!check_path(game))
		return (false);
    printf("::::check texturespath\n");
    if (!check_color(game, game->f_color) || !check_color(game, game->c_color))
        return (false);
    printf("::::check texturescolor\n");
    return (true);
}