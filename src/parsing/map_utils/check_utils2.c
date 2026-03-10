/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:36:35 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/06 13:03:28 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char *skip_spaces(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return line;
}

bool    empty_line(char *str)
{
    char *trimmed;
    
    trimmed = skip_spaces(str);
    return (*trimmed == '\0' || *trimmed == '\n');
}

int valid_line(char *tofind, char *line)
{
    int i;
    
    i = 0;
    if (!line || !line[0])
        return (0);
    while (line[i])
    {
        if (!ft_strchr(tofind, line[i]))
            return (0);
        i++;
    }
    return (1);
}

