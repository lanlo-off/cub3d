/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:27:25 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/11 09:29:23 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	count_raw(t_game *game, char *map_path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error(game, ERR_FILE_OPEN);
	else
	{
		line = get_next_line(fd);
		while (line)
        {
			(line_count++, free(line));
            line = get_next_line(fd);
        }
		close(fd);
	}
	return (line_count);
}

bool fill_raw(t_game *game)
{
    int     i;
    int     fd;
    char    *line;

    i = 0;
	fd = open(game->map_path, O_RDONLY);
	if (fd < 0)
		ft_error(game, ERR_FILE_OPEN);
    game->map->raw = malloc(sizeof(char *) * (count_raw(game, game->map_path) + 1));
    if (!game->map->raw)
        return (ft_error(game, ERR_MALLOC), false);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        game->map->raw[i++] = line;
    }
    close(fd);
    game->map->raw[i] = NULL;
    return (true);
}
