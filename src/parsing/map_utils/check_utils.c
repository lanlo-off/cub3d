/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:12:51 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/11 09:25:55 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool	valid_path(char *arg)
{
	int	fd;

	if (is_file_valid(arg, EXT_XPM) != EXT_XPM)
		return (false);
	fd = open(arg, O_RDONLY);
	if (fd > 0)
		return (close(fd), true);
	return (false);
}

char *skip_identifier(t_game *game, char *line)
{
    int i = 0;

    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != 'F' && line[i] != 'C')
        ft_error(game, ERR_MAP_CHARS);
    i++;
    if (line[i] != ' ' && line[i] != '\t')
        ft_error(game, ERR_MAP_CHARS);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return (&line[i]);
}

int    count_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i] != NULL)
        i++;
    return (i);    
}

int check_rgb_value(char *rgb)
{
    char *trimmed;
    int value;

    trimmed = ft_strtrim(rgb, " \t\n");
    if (!is_numeric_string(trimmed))
        return (free(trimmed), -1);
    value = ft_atoi(trimmed);
    if (value < 0 || value > 255)
        return (free(trimmed), -1);
    free(trimmed);
    return (value);
}

bool    is_last(t_game *game)
{
    int i;

    i = game->map->end;
    while (game->map->raw[i])
    {
        if (!empty_line(game->map->raw[i]))
            return (false);
        i++;
    }
    return (true);
}
