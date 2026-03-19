/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:36:35 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/19 15:08:28 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

bool	empty_line(char *str)
{
	char	*trimmed;

	trimmed = skip_spaces(str);
	return (*trimmed == '\0' || *trimmed == '\n');
}

int	valid_line(char *tofind, char *line)
{
	int	i;

	i = 0;
	if (!line || !line[0] || line[0] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr(tofind, line[i]))
			return (0);
		i++;
	}
	return (1);
}

bool	is_numeric_string(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_identifier_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (true);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (true);
	return (false);
}

bool	no_invalid_char_found(t_game *g)
{
	int		i;
	char	*line;

	i = 0;
	while (g->map->raw[i])
	{
		if (empty_line(g->map->raw[i]))
		{
			i++;
			continue ;
		}
		line = skip_spaces(g->map->raw[i]);
		if (!is_identifier_line(line)
			&& !valid_line(" \t01NSEW\n", g->map->raw[i]))
			return (false);
		i++;
	}
	return (true);
}
