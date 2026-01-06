/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:53:33 by llechert          #+#    #+#             */
/*   Updated: 2026/01/06 17:55:22 by llechert         ###   ########.fr       */
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
	int	x;
	int	y;
	int	dir_x;
	int	dir_y;
	int	plane_x;
	int	plane_y;
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

typedef struct s_game
{
	t_mlx		*mlx;//pour toute la mlx
	t_img		*img;//pour le buffer de rendu : on cree l'image ici avant de l'afficher en une fois sur la fenetre
	t_map		*map;//pour la map post-parsing
	t_player	*player;//pour pos et orientation
	t_textures	*textures;
	t_color		*floor_color;
	t_color		*ceiling_color;
}	t_game;

#endif