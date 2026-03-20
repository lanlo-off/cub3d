/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:51:26 by llechert          #+#    #+#             */
/*   Updated: 2026/03/19 14:58:11 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	print_map(char **grid)
// {
// 	int	i;

// 	i = 0;
// 	while (grid[i])
// 	{
// 		printf("%d -> %s\n",i , grid[i]);
// 		i++;
// 	}
// 	printf("map finie\n\n");
// }

void	load_tex(t_mlx *mlx, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error loading texture\n");
		return ;
	}
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
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
	if (!g->mlx || !g->tex_no || !g->tex_so || !g->tex_we || !g->tex_ea)
		return (false);
	load_tex(g->mlx, g->tex_no, g->tex_no->path);
	load_tex(g->mlx, g->tex_so, g->tex_so->path);
	load_tex(g->mlx, g->tex_we, g->tex_we->path);
	load_tex(g->mlx, g->tex_ea, g->tex_ea->path);
	return (true);
}
