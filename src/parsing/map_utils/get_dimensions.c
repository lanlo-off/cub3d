/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:27:25 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/06 11:54:58 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	count_raw(char *map_path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error();
	else
	{
		while (line = get_next_line(fd))
			(line_count++, free(line));
		close(fd);
	}
	return (line_count);
}

bool fill_raw(t_game *game)
{
    int     i;
    int     fd;
    char    **raw;
    char    *line;

    i = 0;
	fd = open(game->map_path, O_RDONLY);
	if (fd < 0)
		ft_error();
    raw = malloc(sizeof(char *) * count_raw(game->map_path) + 1);
    if (!raw)
        return (false, ft_error());
    while (line = get_next_line(fd))
    {
        raw[i++] = line;
        free(line);
    }
    close(fd);
    raw[i] = 0;
    return (true);
}