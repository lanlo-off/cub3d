/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:35:35 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 10:13:01 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Dessine un bloc bleu de TILE_SIZE x TILE_SIZE avec une marge de 5px entre chaque tile
static void draw_block_img(char *img_data, int img_width, int x, int y)
{
	int i;
	int j;
	t_color color;
	int px;
	int py;
	int pos;

	set_color(&color, "blue");
	i = 0;
	while (i < TILE_SIZE - MARGIN)
	{
		j = 0;
		while (j < TILE_SIZE - MARGIN)
		{
			px = x + i;
			py = y + j;
			pos = (py * img_width + px) * 4;
			img_data[pos + 0] = color.b;
			img_data[pos + 1] = color.g;
			img_data[pos + 2] = color.r;
			img_data[pos + 3] = 0;
			j++;
		}
		i++;
	}
}

// Dessine un cercle blanc de rayon 5 centré sur la position pixel du joueur
static void draw_player_img(char *img_data, int img_width, t_player *player)
{
	int x;
	int y;
	t_color color;
	int pos;
	double dx, dy;
	double radius = 5;
	int px, py;

	// Conversion coordonnées cases -> pixels 
	px = (int)(player->x * TILE_SIZE);
	py = (int)(player->y * TILE_SIZE);

	set_color(&color, "white");
	y = -(int)radius - 1;
	while (y <= (int)radius + 1)
	{
		x = -(int)radius - 1;
		while (x <= (int)radius + 1)
		{
			dx = x;
			dy = y;
			if (dx * dx + dy * dy <= radius * radius)
			{
				int draw_x = px + (int)dx;
				int draw_y = py + (int)dy;
				pos = (draw_y * img_width + draw_x) * 4;
				img_data[pos + 0] = color.b;
				img_data[pos + 1] = color.g;
				img_data[pos + 2] = color.r;
				img_data[pos + 3] = 0;
			}
			x++;
		}
		y++;
	}
}

// Dessine les murs dans l'image avec une marge entre chaque tile
static void print_wall_img(char **grid, char *img_data, int img_width)
{
	int i;
	int j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == '1')
				draw_block_img(img_data, img_width, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void print_minimap(t_game *game, t_mlx *mlx, t_img *img)
{
	int	nb_ray;

	nb_ray = 0;
	// img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, mlx->win_width, mlx->win_height);
	// img->address = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	// reset_background(img);
	print_wall_img(game->map->grid, img->address, mlx->win_width);
	draw_player_img(img->address, mlx->win_width, game->player);
	while (nb_ray < MM_NB_RAY)//On veut faire 60 rayons max (1 par degres)
	{
		printf("nb_ray : [%i]\n", nb_ray);
		mm_print_ray_img(game, game->map, game->player, nb_ray);
		nb_ray++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
	// mlx_destroy_image(mlx->mlx_ptr, img->img_ptr);
}