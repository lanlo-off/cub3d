/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiotla <mmiotla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:32:24 by llechert          #+#    #+#             */
/*   Updated: 2026/03/12 17:05:00 by mmiotla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*#############   PERMANENT   ###########*/

# include "struct.h"
# include "keycode.h"
# include <math.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 450
# define TILE_SIZE 64
# define MARGIN 5
# define FOV 60
# define MM_WIDTH
# define MM_HEIGTH
# define MM_NB_RAY 120
# define ROT_SPEED 0.01//en faisant WIN_WINDTH / 100000 on a un truc correct
# define MOV_SPEED 0.01//a voir
# define EPSILON 1e-5//Protection pour le ray_casting pour eviter de diviser par des nombres trop petits et crash
# define M_PI 3.14159265358979323846
# define MSG_ERR_ARG "Invalid number of arguments"
# define MSG_ERR_FILE_EXT "Wrong file extension (must be .cub)"
# define MSG_ERR_FILE_OPEN "Could not open file or FD invalid"
# define MSG_ERR_MALLOC "Memory allocation failed"
# define MSG_ERR_MAP_EMPTY "Map is empty or totally invalid"
# define MSG_ERR_MAP_UNCLOSED "Map is not fully enclosed by walls"
# define MSG_ERR_MAP_CHARS "Invalid characters found in map"
# define MSG_ERR_TEX_DUP "Duplicate texture or color identifier"
# define MSG_ERR_TEX_MISSING "Missing or invalid texture path"
# define MSG_ERR_COLOR_FORMAT "Invalid RGB format"
# define MSG_ERR_COLOR_RANGE "RGB values must be between 0 and 255"

/*#############   FREE & UTILS   ###########*/
/*free.c*/
void	free_map(t_map *map);
void	free_tex(t_game *g, t_tex *tex);
void	free_mlx(t_mlx *mlx);
void	free_img(t_game *game, t_img *img);
int		exit_game(t_game *game);
void    free_game(t_game *game);

/*#############   INIT   ###########*/

/*init.c*/
bool	init_struct(t_game *g);
bool	init_game(t_game *game);

/*init_utils.c*/
bool	init_textures(t_game *g);
bool	init_map(t_game *g);
bool	get_player_start(char **map, t_player *player);

/*error_init.c*/
void	error_init_mlx(t_game *game);
void	error_init_win(t_game *game, t_mlx *mlx);
void	error_init_img(t_game *game);
void	error_init_player(t_game *game, t_player *player);

/*#############   GAME   ###########*/

/*hook.c*/
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		game_loop(t_game *game);

/*hook_utils.c*/
void	rotate(t_player *player, double rot);
bool	is_in_map(double x, int value);

/*print_image.c*/
void	print_img(t_game *game, void *img, int i, int j);
void	put_pixel(t_img *img, int x, int y, int color);
void	reset_background(t_img *img);

/*dda.c*/
void	get_ray_values(t_ray *ray, t_player *player);
bool	calculate_hitpoint(t_game *g, t_ray *ray, t_map *map, t_player *player);

/*render.c*/
void	render(t_game *game, t_mlx *mlx, t_img *img);

/*render_utils.c*/
int		rgb_to_int(t_color *color);
int		get_color_from_xpm(int x, int y, t_tex *tex);


/*#############   MINIMAP   ###########*/
void	print_minimap(t_game *game, t_mlx *mlx, t_img *img);
bool	mm_print_ray_img(t_game *game, t_map *map, t_player *player, int nb_ray);
void	mm_get_ray_values(t_ray *ray, t_player *player);
bool	mm_calculate_hitpoint(t_ray *ray, t_map *map, t_player *player);

/*#############   PARSING   ###########*/
int		is_file_valid(const char *filename, t_extension expected);
bool	valid_path(char *arg);
char	*skip_identifier(t_game *game, char *line);
bool    findmap_elements(t_game *game);
bool    check_texture(t_game *game);
char    *skip_spaces(char *line);
bool    empty_line(char *str);
int	    count_raw(t_game *game, char *map_path);
int     valid_line(char *tofind, char *line);
bool    fill_raw(t_game *game);
bool    fill_grid(t_game *game);
bool    is_last(t_game *game);
bool    check_player_pos(t_map *map);
bool    check_map_closed(t_map *map);
bool    parser(t_game *game);
int     count_tab(char **tab);
int     check_rgb_value(char *rgb);
bool    is_numeric_string(char *str);

/*#############   ERRORS SYSTEM   ###########*/
void    ft_error(t_game *game, t_err_code code);
void    print_error(t_err_code code);

/*#############   TEMPORAIRE   ###########*/
/*tmp_utils.c*/
void	print_map(char **grid);
void	get_map(t_map *map, const char *filename);
int		count_line_len(const char *filename);
int		count_lines(const char *filename);
bool	load_textures(t_game *g);
bool	set_floor_ceiling_color(t_game *g);
void	set_color(t_color *color, char *name);
void    free_tab(char **tab);


#endif