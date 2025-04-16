/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_helpers2_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:22:08 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 19:22:09 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	update_anim(t_weapon_anim *anim, long long current_ms)
{
	if (anim->is_playing
		&& current_ms - anim->last_frame_time > ANIM_FRAME_DELAY)
	{
		anim->current_frame++;
		anim->last_frame_time = current_ms;
		if (anim->current_frame >= anim->num_frames)
		{
			anim->current_frame = 0;
			anim->is_playing = false;
		}
	}
}

void	update_weapon_animation(t_game *game)
{
	struct timeval	current_time;
	long long		current_ms;

	gettimeofday(&current_time, NULL);
	current_ms = (current_time.tv_sec * 1000LL) + (current_time.tv_usec / 1000);
	update_anim(&game->shotgun_anim, current_ms);
	update_anim(&game->pistol_anim, current_ms);
	update_anim(&game->punch_anim, current_ms);
}

void	init_textures(t_game *game)
{
	init_walls(game);
	init_weapons(game);
}
