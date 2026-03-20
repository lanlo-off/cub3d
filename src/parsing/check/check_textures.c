/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:57:21 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/19 15:11:51 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool	check_color(t_game *game, t_color *color)
{
	char	**rgb;

	rgb = ft_split(color->line, ',');
	if (!rgb || count_tab(rgb) != 3)
	{
		if (rgb)
			free_tab(rgb);
		return (ft_error(game, ERR_COLOR_RANGE), false);
	}
	color->r = check_rgb_value(rgb[0]);
	color->g = check_rgb_value(rgb[1]);
	color->b = check_rgb_value(rgb[2]);
	if (color->r >= 0 && color->g >= 0 && color->b >= 0)
		return (free_tab(rgb), true);
	free_tab(rgb);
	return (false);
}

static bool	check_path(t_game *game)
{
	if (!valid_path(game->tex_ea->path))
		return (false);
	if (!valid_path(game->tex_no->path))
		return (false);
	if (!valid_path(game->tex_so->path))
		return (false);
	if (!valid_path(game->tex_we->path))
		return (false);
	return (true);
}

bool	check_texture(t_game *game)
{
	if (!check_path(game))
		return (ft_error(game, ERR_TEX_PATH), false);
	if (!check_color(game, game->f_color) || !check_color(game, game->c_color))
		return (ft_error(game, ERR_COLOR_RANGE), false);
	return (true);
}
