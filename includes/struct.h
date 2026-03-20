/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:53:33 by llechert          #+#    #+#             */
/*   Updated: 2026/03/12 19:03:22 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

typedef enum e_extension
{
	EXT_UNKNOWN = -1,
	EXT_ISDIR = 0,
	EXT_CUB = 1,
	EXT_XPM = 2
}				t_extension;

typedef enum e_err_code
{
	ERR_ARG,
	ERR_FILE_EXT,
	ERR_FILE_OPEN,
	ERR_MALLOC,
	ERR_MAP_EMPTY,
	ERR_MAP_UNCLOSED,
	ERR_MAP_CHARS,
	ERR_MAP_FIND,
	ERR_MAP_LAST,
	ERR_TEX_NUMBER,
	ERR_TEX_PATH,
	ERR_COLOR_NUMBER,
	ERR_COLOR_RANGE,
	ERR_PLAYER_NUMBER
}				t_err_code;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_width;
	int			win_height;
}				t_mlx;

typedef struct s_img
{
	void		*img_ptr;
	char		*address;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_map
{
	char		**raw;
	char		**grid;
	int			start;
	int			end;
	int			width;
	int			height;
	int			max;
	int			*p_pos;
	int			p_flag;
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_tex
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
	int			flag;
	char		*path;
}				t_tex;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	char		*line;
	int			flag;
}				t_color;

typedef enum s_frontier
{
	VERTICAL,
	HORIZONTAL,
}				t_frontier;

typedef struct s_ray
{
	int			index;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		perp_dist;
	double		hit_x;
	double		hit_y;
	t_frontier	frontier_type;
	t_tex		*wall_texture;

	int			wall_start;
	int			wall_height;
	int			wall_end;
}				t_ray;

typedef struct s_key
{
	bool		w;
	bool		a;
	bool		s;
	bool		d;
	bool		left;
	bool		right;
}				t_key;

typedef struct s_game
{
	t_mlx		*mlx;
	t_img		*img;
	t_map		*map;
	t_player	*player;
	t_tex		*tex_no;
	t_tex		*tex_so;
	t_tex		*tex_we;
	t_tex		*tex_ea;
	t_color		*f_color;
	t_color		*c_color;
	t_key		*key;
	int			tile_size;
	char		*map_path;
}				t_game;

#endif