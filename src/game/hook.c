/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:42:58 by llechert          #+#    #+#             */
/*   Updated: 2026/01/15 18:03:08 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	try_moving(t_player *p, t_map *m, double dx, double dy)
{
	double new_x;
	double new_y;
	
	new_x = p->x + dx;
	new_y = p->y + dy;
	if (is_in_map(new_x, m->width) && m->grid[(int)p->y][(int)new_x] == '0')
		p->x = new_x;
	if (is_in_map(new_y, m->height) && m->grid[(int)new_y][(int)p->x] == '0')
		p->y = new_y;
}

static void	move_player(t_game *g, t_key *key, t_player *p)
{
	double	move_x;
	double	move_y;
	double	len;

	move_x = 0.0;
	move_y = 0.0;
	/*1- gestion du mouvement vers l'avant ou arriere*/
	move_x = p->dir_x * (key->w - key->s);
	move_y = p->dir_y * (key->w - key->s);
	/*2- gestion du strafe*/
	move_x += p->plane_x * (key->d - key->a);
	move_y += p->plane_y * (key->d - key->a);
	/*3- Normalisation du deplacement pour eviter acceleration en strafing*/
	len = sqrt(move_x * move_x + move_y * move_y);
	if (len > 0)
	{
		move_x /= len;
		move_y /= len;
	}
	/*4- On verifie s'il y a un mur et on bouge si c'est ok*/
	try_moving(p, g->map, move_x * MOV_SPEED, move_y * MOV_SPEED);
}

int	game_loop(t_game *game)
{
	if (game->key->left)
		(rotate(game->player, -ROT_SPEED), printf("Rot gauche\n"));
	if (game->key->right)
		(rotate(game->player, ROT_SPEED), printf("Rot droite\n"));
	move_player(game, game->key, game->player);
	// print_minimap(game, game->mlx, game->img);
	print_map(game, game->mlx, game->img);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	if (keycode == KEY_LEFT)
		game->key->left = true;
	if (keycode == KEY_RIGHT)
		game->key->right = true;
	if (keycode == KEY_W)
		game->key->w = true;
	if (keycode == KEY_S)
		game->key->s = true;
	if (keycode == KEY_A)
		game->key->a = true;
	if (keycode == KEY_D)
		game->key->d = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT)
		game->key->left = false;
	if (keycode == KEY_RIGHT)
		game->key->right = false;
	if (keycode == KEY_W)
		game->key->w = false;
	if (keycode == KEY_S)
		game->key->s = false;
	if (keycode == KEY_A)
		game->key->a = false;
	if (keycode == KEY_D)
		game->key->d = false;
	return (0);
}

