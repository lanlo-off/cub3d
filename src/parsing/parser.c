/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:00:39 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/12 14:48:43 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	read_map(t_game *game)
{
	int		fd;

	fd = open(game->map_path, O_RDONLY);
	if (fd < 0)
		return (ft_error(game, ERR_FILE_OPEN), false);
	close(fd);
    return (true);
}

bool    parser(t_game *game)
{
    //if (is_file_valid(game->map_path, EXT_CUB) != EXT_CUB)
    //    ft_error(game, ERR_FILE_EXT);
    if (!read_map(game))
        return (false);
    printf("::readmap\n");
    if (!findmap_elements(game))
        ft_error(game, ERR_MAP_CHARS);
    printf("::findmap elements\n");
    if (!is_last(game))
        ft_error(game, ERR_MAP_CHARS);
    printf("::is last\n");
    if (!check_texture(game))
        ft_error(game, ERR_COLOR_FORMAT);
    printf("::check text + color\n");
    if (!check_map_closed(game->map))
        ft_error(game, ERR_MAP_UNCLOSED);
    printf("::map closed ?\n");
    return (true);
}
