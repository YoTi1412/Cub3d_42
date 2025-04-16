/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:20:29 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/08 15:52:11 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
	if (key == KEY_SPACE)
		game->pressed.space = true;
	if (key == KEY_RIGHT)
		game->pressed.right = true;
	if (key == KEY_LEFT)
		game->pressed.left = true;
	return (0);
}

int	key_action(int key, t_game *game)
{
	if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W
		|| key == KEY_RIGHT || key == KEY_LEFT || key == KEY_ESC
		|| key == KEY_SPACE)
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
	if (key == KEY_SPACE && game->pressed.space)
		game->pressed.space = false;
	if (key == KEY_LEFT && game->pressed.left)
		game->pressed.left = false;
	if (key == KEY_RIGHT && game->pressed.right)
		game->pressed.right = false;
	return (0);
}
