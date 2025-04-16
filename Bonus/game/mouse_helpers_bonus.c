/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_helpers_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:03:18 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:47:33 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	handle_weapon_fire(t_game *game, long long current_ms)
{
	if (game->type_weapon == SHOTGUN && !game->shotgun_anim.is_playing)
	{
		game->shotgun_anim.is_playing = true;
		game->shotgun_anim.current_frame = 0;
		game->shotgun_anim.last_frame_time = current_ms;
	}
	else if (game->type_weapon == PISTOL && !game->pistol_anim.is_playing)
	{
		game->pistol_anim.is_playing = true;
		game->pistol_anim.current_frame = 0;
		game->pistol_anim.last_frame_time = current_ms;
	}
	else if (game->type_weapon == PUNCH && !game->punch_anim.is_playing)
	{
		game->punch_anim.is_playing = true;
		game->punch_anim.current_frame = 0;
		game->punch_anim.last_frame_time = current_ms;
	}
}

int	mouse_hook(int keycode, int x, int y, t_game *game)
{
	struct timeval	current_time;
	long long		current_ms;

	(void)x;
	(void)y;
	gettimeofday(&current_time, NULL);
	current_ms = current_time.tv_sec * 1000LL + current_time.tv_usec / 1000;
	if (keycode == KEY_MOUSE_LEFT)
		handle_weapon_fire(game, current_ms);
	else if (keycode == MOUSE_SDOWN)
		scroll_down(game);
	else if (keycode == MOUSE_SUP)
		scroll_up(game);
	return (0);
}
