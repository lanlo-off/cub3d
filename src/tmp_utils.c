/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:51:26 by llechert          #+#    #+#             */
/*   Updated: 2026/01/16 13:40:37 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int count_lines(const char *filename)
{
	FILE *f = fopen(filename, "r");
	int count = 0;
	char buf[1024];
	if (!f)
		return 0;
	while (fgets(buf, sizeof(buf), f))
		count++;
	fclose(f);
	return count;
}

// Fonction utilitaire pour la longueur max d'une ligne
int count_line_len(const char *filename)
{
	FILE *f = fopen(filename, "r");
	int max = 0;
	char buf[1024];
	int len;
	if (!f)
		return 0;
	while (fgets(buf, sizeof(buf), f))
	{
		len = (int)ft_strlen(buf);
		if (buf[len-1] == '\n')
			len--;
		if (len > max)
			max = len;
	}
	fclose(f);
	return max;
}

// Fonction principale pour récupérer la map
void get_map(t_map *map, const char *filename)
{
	FILE *f;
	int i;
	int width, height;
	char buf[1024];

	if (!map || !filename)
		return;
	height = count_lines(filename);
	width = count_line_len(filename);
	if (height <= 0 || width <= 0)
		return;
	map->grid = malloc(sizeof(char *) * (height + 1));
	if (!map->grid)
		return;
	map->width = width;
	map->height = height;
	f = fopen(filename, "r");
	if (!f)
		return;
	i = 0;
	while (fgets(buf, sizeof(buf), f) && i < height)
	{
		int len = (int)strlen(buf);
		if (len > 0 && buf[len-1] == '\n')
			buf[--len] = '\0';
		map->grid[i] = malloc(width + 1);
		if (!map->grid[i])
			break;
		ft_memset(map->grid[i], '1', width); // remplir de murs par défaut
		map->grid[i][width] = '\0';
		if (len > 0)
			ft_memcpy(map->grid[i], buf, len > width ? width : len);
		i++;
	}
	while (i < height) // lignes manquantes = murs
	{
		map->grid[i] = malloc(width + 1);
		if (map->grid[i])
		{
			ft_memset(map->grid[i], '1', width);
			map->grid[i][width] = '\0';
		}
		i++;
	}
	map->grid[i] = NULL;
	fclose(f);
}

void	print_map(char **grid)
{
	int	i;
	
	i = 0;
	while (grid[i])
	{
		printf("%s\n", grid[i]);
		i++;
	}
	printf("map finie\n\n");
}

void	load_tex(t_mlx *mlx, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error loading texture\n");
		return ;
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	// printf("img [%p] | addr [%p] | width [%d] | height [%d]\n", tex->img, tex->addr, tex->width, tex->height);
}

/**
 * @brief Sert a charger les textures a partir des fichiers xpm
 * N.B. a la fin du programme il faut simplement appeler
 * if (tex->img)
        mlx_destroy_image(mlx->mlx_ptr, tex->img);
		Pas d'autres free a faire sauf free(tex)
 * 
 * @param g 
 * @return true 
 * @return false 
 */
bool	load_textures(t_game *g)
{
	// printf("mlx [%p] | tex_NO [%p] | tex_SO [%p] | tex_WE [%p] | tex_EA [%p]\n", g->mlx, g->tex_NO, g->tex_SO, g->tex_WE, g->tex_EA);
	if (!g->mlx || !g->tex_NO || !g->tex_SO || !g->tex_WE || !g->tex_EA)
		return (false);
	// load_tex(g->mlx, g->tex_NO, "./textures/wall_NO.xpm");
	// load_tex(g->mlx, g->tex_SO, "./textures/wall_SO.xpm");
	// load_tex(g->mlx, g->tex_WE, "./textures/wall_WE.xpm");
	// load_tex(g->mlx, g->tex_EA, "./textures/wall_EA.xpm");
	load_tex(g->mlx, g->tex_NO, "./textures/brick.xpm");
	load_tex(g->mlx, g->tex_SO, "./textures/iron.xpm");
	load_tex(g->mlx, g->tex_WE, "./textures/stone.xpm");
	load_tex(g->mlx, g->tex_EA, "./textures/wood.xpm");
	return (true);
}

bool	set_floor_ceiling_color(t_game *g)
{
	g->ceiling_color = ft_calloc(1, sizeof(t_color));
	if (!g->ceiling_color)
		return (false);
	g->floor_color = ft_calloc(1, sizeof(t_color));
	if (!g->ceiling_color)
		return (free(g->ceiling_color), false);
	g->floor_color->r = 139;
	g->floor_color->g = 69;
	g->floor_color->b = 19;
	g->ceiling_color->r = 135;
	g->ceiling_color->g = 206;
	g->ceiling_color->b = 235;
	return (true);
}

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