/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime.m <maxime.m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:05:23 by mmiotla           #+#    #+#             */
/*   Updated: 2026/03/10 15:49:30 by maxime.m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_error(t_err_code code)
{
    static const char *messages[] = {
        MSG_ERR_ARG,
        MSG_ERR_FILE_EXT,
        MSG_ERR_FILE_OPEN,
        MSG_ERR_MALLOC,
        MSG_ERR_MAP_EMPTY,
        MSG_ERR_MAP_UNCLOSED,
        MSG_ERR_MAP_CHARS,
        MSG_ERR_TEX_DUP,
        MSG_ERR_TEX_MISSING,
        MSG_ERR_COLOR_FORMAT,
        MSG_ERR_COLOR_RANGE
    };

    ft_putstr_fd("Error\n", 2);
    ft_putendl_fd((char *)messages[code], 2);
}

void	ft_error(t_game *game, t_err_code code)
{
    print_error(code);
    free_game(game);
    exit(EXIT_FAILURE);
}