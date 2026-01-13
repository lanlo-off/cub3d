/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:35:35 by llechert          #+#    #+#             */
/*   Updated: 2026/01/13 15:55:34 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void set_color(t_color *color, char *name)
{
	if (!color || !name)
		return;
	if (ft_strcmp(name, "blue") == 0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 255;
	}
	else if (ft_strcmp(name, "white") == 0)
	{
		color->r = 255;
		color->g = 255;
		color->b = 255;
	}
	else if (ft_strcmp(name, "green") == 0)
	{
		color->r = 0;
		color->g = 255;
		color->b = 0;
	}
	else if (ft_strcmp(name, "black") == 0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else if (ft_strcmp(name, "red") == 0)
	{
		color->r = 255;
		color->g = 0;
		color->b = 0;
	}
}

// Dessine un bloc bleu de TILE_SIZE x TILE_SIZE avec une marge de 5px entre chaque tile
void draw_block_img(char *img_data, int img_width, int x, int y)
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
void draw_player_img(char *img_data, int img_width, t_player *player)
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
void print_wall_img(char **grid, char *img_data, int img_width)
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

bool	get_player_start(char **map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(i, j, map[i][j], player))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

void print_minimap(t_game *game, t_mlx *mlx, t_img *img)
{
	int	nb_ray;

	nb_ray = 0;
	img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, mlx->win_width, mlx->win_height);
	printf("img_ptr = [%p]\n", img->img_ptr);
	img->address = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	get_player_start(game->map->grid, game->player);
	fill_player_data(game->player);
	print_wall_img(game->map->grid, img->address, mlx->win_width);
	draw_player_img(img->address, mlx->win_width, game->player);
	while (nb_ray < FOV)//On veut faire 60 rayons max (1 par degres)
	{
		print_ray_img(game, game->map, game->player, nb_ray);
		nb_ray++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);

}