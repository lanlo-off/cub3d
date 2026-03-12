/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:35:44 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/12 14:40:30 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_dir(const char *arg)
{
	int	fd;

	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
		return (close(fd), true);
	return (false);
}

t_extension	get_ext(const char *filename)
{
	int	len;

	if (!filename)
		return (EXT_UNKNOWN);
	if (is_dir(filename))
		return (EXT_ISDIR);
	len = ft_strlen(filename);
	if (len >= 4 && ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (EXT_CUB);
	if (len >= 4 && ft_strncmp(filename + len - 4, ".xpm", 4) == 0)
		return (EXT_XPM);
	return (EXT_UNKNOWN);
}

int	is_file_valid(const char *filename, t_extension expected)
{
	t_extension	ext;

	ext = get_ext(filename);
	if (ext == EXT_UNKNOWN)
		return (EXT_UNKNOWN);
	if (ext == EXT_ISDIR)
		return (EXT_UNKNOWN);
	if (ext != expected)
		return (EXT_UNKNOWN);
	return (ext);
}
