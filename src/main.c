/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:41:18 by llechert          #+#    #+#             */
/*   Updated: 2026/01/14 19:30:03 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


// Fonction utilitaire pour compter les lignes d'un fichier
static int count_lines(const char *filename)
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
static int count_line_len(const char *filename)
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

int	main(int ac, char **av)
{
	t_game	*game;
	t_map	*map;

	if (ac != 2)
	{
		printf("Wrong number of arguments : ./cub3d map.cub\n");
		return (1);
	}
	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		return (1);
	// if (!parse(av[1], game))//voir dans idees.txt ce dont on a besoin pour apres
	//     return (1);
	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (1);
	ft_memset(map, 0, sizeof(t_map));
	get_map(map, av[1]);
	game->map = map;
	// print_map(map->grid);
	init_struct(game);
	print_minimap(game, game->mlx, game->img);
	mlx_loop(game->mlx->mlx_ptr);
	exit_game(game);
	// free_all_exit(game);
	return (0);
}
