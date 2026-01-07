/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:32:24 by llechert          #+#    #+#             */
/*   Updated: 2026/01/07 19:19:03 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define TILE_SIZE 50
# define MARGIN 5

/*error_init.c*/
void	error_init_mlx(t_game *game);
void	error_init_win(t_game *game, t_mlx *mlx);
void	error_init_img(t_game *game);

/*free.c*/
void	free_map(t_map *map);
void	free_textures(t_textures *textures);
void	free_mlx(t_mlx *mlx);
void	free_img(t_img *img);
int		exit_game(t_game *game);


/*init.c*/
bool	init_struct(t_game *game);

/*player.c*/
bool	is_player(int i, int j, char c, t_player *player);

/*ray.c*/
bool	print_ray(t_map *map, t_player *player, char *img_data);

/*wip.c*/
void	print_minimap(t_game *game, t_mlx *mlx, t_img *img);


/*###########TEMPORAIRE##############*/


#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef enum s_wall
{
	VERTICAL,
	HORIZONTAL,
}	t_wall;

typedef struct s_ray
{
	double	dir_x;//se calcule avec la direction du joueur
	double	dir_y;//player.dir + player.plane (a voir plus tard)
	int	map_x;//coordonnees de la case actuellement traversee
	int	map_y;
	double	side_dist_x;//distance du rayon jusqu'a la prochaine frontiere de case
	double	side_dist_y;//i.e pour sortir de la case dans laquelle le joueur est
	double	delta_dist_x;//distance a parcourir pour traverser 1 case entiere
	double	delta_dist_y;//depend donc de la direction du rayon (pythagore)
	int	step_x;//+1 avance vers la droite ou -1 vers la gauche (se deduit de dir_x) -> quand on traverse une frontiere verticale map_x += step_x 
	int	step_y;//+1 avance vers le bas ou -1 vers le haut (se deduit de dir_y) -> quand on traverse une frontiere horizontale map_y += step_y
	t_wall	wall_type;//indique si le mur touche est 0=vertical ou 1=horizontal. ca + la direction donne N/S/E/W pour l'image a input sur le mur
	double	perp_dist;//distance perpendiculaire du joueur au mur (pour calculer la hauteur du mur a l'ecran) = pythagore en construisant un triangle rectangle ayant pour sommets : le joueur, le point du mur rencontre et en 3 l'intersection entre perpendiculaire du mur et perpendiculaire a cette perpendiculaire passant par le joueur
}	t_ray;

#endif