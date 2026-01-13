/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:53:33 by llechert          #+#    #+#             */
/*   Updated: 2026/01/13 16:03:34 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_width;
	int		win_height;
}	t_mlx;

//ecrire un pixel en (x,y) : 
//1- verifier que x est dans [0;width[ et y dans [0; height[ 
//2- puis offset = y * line_len + x * (bpp/8) 
//=> on peut ecrire un int a address + offset
typedef struct s_img
{
	void	*img_ptr;//pointeur qui contient toute l'image (on le passera a mlx_put_image_to_window)
	char	*address;//pointeur vers le debut du buffer de pixel -> l'endroit ou on ecrit les pixels a la main
	int		bpp;//bit par pixel 32 ou 64, on aura ensuite byte par pixel = bpp/8 (pour fonction mlx)
	int		line_len;//nb de bytes par ligne
	int		endian;//0 = little ; 1 = big ?
	int		width;//on stocke car sinon on recupere jamais ces infos via la mlx
	int		height;//same
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
	void	*pixels;
}	t_texture;

typedef struct s_textures
{
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
}	t_textures;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef enum s_frontier
{
	VERTICAL,
	HORIZONTAL,
}	t_frontier;

typedef struct s_ray
{
	int		index;
	double	dir_x;//= cos de l'angle ; se calcule avec la direction du joueur
	double	dir_y;//= sin de l'angle ; player.dir + player.plane (a voir plus tard)
	int	map_x;//coordonnees de la case actuellement traversee par le joueur
	int	map_y;
	double	side_dist_x;//distance du rayon jusqu'a la prochaine frontiere de case
	double	side_dist_y;//i.e pour sortir de la case dans laquelle le joueur est
	double	delta_dist_x;//distance a parcourir pour traverser 1 case entiere
	double	delta_dist_y;//depend donc de la direction du rayon (pythagore)
	int	step_x;//+1 avance vers la droite ou -1 vers la gauche (se deduit de dir_x) -> quand on traverse une frontiere verticale map_x += step_x 
	int	step_y;//+1 avance vers le bas ou -1 vers le haut (se deduit de dir_y) -> quand on traverse une frontiere horizontale map_y += step_y
	t_frontier	frontier_type;//indique si la frontiere rencontree a ce moment est 0=vertical ou 1=horizontal. ca sur la derniere frontiere (la rencontre du mur) + la direction donne N/S/E/W pour l'image a input sur le mur
	t_texture	*wall_texture;//Se deduit de wall type + direction, ensuite on reutilise une des textures definie en fonction 
	double	perp_dist;//distance perpendiculaire du joueur au mur (pour calculer la hauteur du mur a l'ecran) = pythagore en construisant un triangle rectangle ayant pour sommets : le joueur, le point du mur rencontre et en 3 l'intersection entre perpendiculaire du mur et perpendiculaire a cette perpendiculaire passant par le joueur
	double	hit_x;//point d'impact sur le mur
	double	hit_y;
}	t_ray;

/*On sait que pour chaque ray (chaque colonne de la fenetre):
- Du joueur au point d'impact, on colore en floor
- ensuite on met les pixels de la texture sur la hauteur du mur (calculable grace a perp dist)
- De la fin du mur a la fin de la fenetre on fait le ceiling*/

typedef struct s_game
{
	t_mlx		*mlx;//pour toute la mlx
	t_img		*img;//pour le buffer de rendu : on cree l'image ici avant de l'afficher en une fois sur la fenetre
	t_map		*map;//pour la map post-parsing
	t_player	*player;//pour pos et orientation
	t_textures	*textures;
	t_color		*floor_color;
	t_color		*ceiling_color;
	int			tile_size;
}	t_game;

#endif