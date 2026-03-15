/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:27:25 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/12 18:53:38 by llechert         ###   ########.fr       */
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
	printf("line count-> %d\n", line_count);
	return (line_count);
}

bool fill_raw(t_game *g)
{
	int     i;
	int     fd;
	char    *line;

	i = 0;
	fd = open(g->map_path, O_RDONLY);
	if (fd < 0)
		ft_error(g, ERR_FILE_OPEN);
	g->map->raw = malloc(sizeof(char *) * (count_raw(g, g->map_path) + 1));
	if (!g->map->raw)
		return (ft_error(g, ERR_MALLOC), false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			get_next_line(-42);
			break;
		}
		g->map->raw[i++] = line;
	}
	(get_next_line(-42), close(fd));
	printf("Last pointer to NULL is -> %d\n", i);
	g->map->raw[i] = NULL;
	return (true);
}
