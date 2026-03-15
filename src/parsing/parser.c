/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parser.c                                          :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mmiotla <mmiotla@student.42.fr>           #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/02/23 12:00:39 by mmiotla          #+#    #+#              */
/*   Updated: 2026/03/15 18:44:06 by mmiotla         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool read_map(t_game *game)
{
	int	fd;

	fd = open(game->map_path, O_RDONLY);
	if (fd < 0)
		return (ft_error(game, ERR_FILE_OPEN), false);
	close(fd);
	return (true);
}

bool parser(t_game *game)
{
	if (!read_map(game))
		ft_error(game, ERR_FILE_OPEN);
	//printf("::readmap\n");
	if (!findmap_elements(game))
		return (false);
	//printf("::findmap elements\n");
	if (!is_last(game))
		ft_error(game, ERR_MAP_LAST);
	//printf("::is last\n");
	if (!check_texture(game))
		return (false);
	//printf("::check text + color\n");
	if (!check_map_closed(game->map))
		ft_error(game, ERR_MAP_UNCLOSED);
	//printf("::map closed ?\n");
	game->map->height = game->map->end - game->map->start + 1;
	game->map->width = game->map->max;
	return (true);
}
