/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:20:29 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:42:37 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	key_hook(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit_game(game);
	if (key == KEY_A)
		game->pressed.a = true;
	if (key == KEY_D)
		game->pressed.d = true;
	if (key == KEY_S)
		game->pressed.s = true;
	if (key == KEY_W)
		game->pressed.w = true;
	if (key == KEY_RIGHT)
		game->pressed.right = true;
	if (key == KEY_LEFT)
		game->pressed.left = true;
	return (0);
}

int	key_action(int key, t_game *game)
{
	if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W
		|| key == KEY_RIGHT || key == KEY_LEFT || key == KEY_ESC)
		key_hook(key, game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_W && game->pressed.w)
		game->pressed.w = false;
	if (key == KEY_S && game->pressed.s)
		game->pressed.s = false;
	if (key == KEY_A && game->pressed.a)
		game->pressed.a = false;
	if (key == KEY_D && game->pressed.d)
		game->pressed.d = false;
	if (key == KEY_LEFT && game->pressed.left)
		game->pressed.left = false;
	if (key == KEY_RIGHT && game->pressed.right)
		game->pressed.right = false;
	return (0);
}
