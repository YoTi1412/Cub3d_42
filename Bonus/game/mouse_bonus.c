/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:03:18 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/12 01:56:23 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	scroll_up(t_game *game)
{
	game->type_weapon = (game->type_weapon + 1) % NUM_WEAPONS;
}

void	scroll_down(t_game *game)
{
	game->type_weapon = (game->type_weapon - 1 + NUM_WEAPONS) % NUM_WEAPONS;
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x;

	if (x < SCREEN_W * 0.1 || x > SCREEN_W * 0.9 || y < SCREEN_H
		* 0.1 || y > SCREEN_H * 0.9)
	{
		mlx_mouse_move(game->mlx, game->mlx_win, SCREEN_W / 2, SCREEN_H
			/ 2);
		last_x = SCREEN_W / 2;
	}
	if (last_x < x)
		rotate_right(game);
	else
		rotate_left(game);
	last_x = x;
	return (0);
}

void	init_event_mouse(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->mlx_win);
	mlx_mouse_move(game->mlx, game->mlx_win, SCREEN_W / 2, SCREEN_H
		/ 2);
	mlx_hook(game->mlx_win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->mlx_win, mouse_hook, game);
}
