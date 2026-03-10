/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:00:39 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/10 12:08:10 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	read_map(t_game *game)
{
	int		fd;

	fd = open(game->map_path, O_RDONLY);
	if (fd < 0) //err ouverture
		return (false, ft_error(game));
	close(fd);
    return (true);
}

bool    parser(t_game *game)
{
    if (!read_map(game))
        return (false);
    if (!findmap_elements(game))
        return (false);
    if (!is_last(game))
        return (false);
    if (!check_texture(game))
        return (false);
    if (!check_map_closed(game->map))
        return (false);
    return (true);
}
