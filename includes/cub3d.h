/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:32:24 by llechert          #+#    #+#             */
/*   Updated: 2026/01/06 18:50:56 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include "struct.h"
# include <stdbool.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

/*error_init.c*/
void	error_init_mlx(t_game *game);
void	error_init_win(t_game *game, t_mlx *mlx);

/*free.c*/
void	free_map(t_map *map);
void	free_textures(t_textures *textures);
void	free_mlx(t_mlx *mlx);
void	free_img(t_img *img);
int		exit_game(t_game *game);


/*init.c*/
bool	init_struct(t_game *game);

/*wip.c*/
void	print_minimap(t_game *game);


/*###########TEMPORAIRE##############*/
typedef struct s_ray
{
	int	dir_x;
	int	dir_y;
	int	map_x;
	int	map_y;
	int	side_dist_x;
	int	side_dist_y;
	int	delta_dist_x;
	int	delta_dist_y;
	int	step_x;
	int	step_y;
	int	side;
	int	perp_dist;
}	t_ray;

#endif