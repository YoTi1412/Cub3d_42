/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:17:52 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 16:04:47 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_weapon_animation(t_game *game, t_weapon_anim *anim,
	const char *path, int frames)
{
	int	i;

	anim->current_frame = 0;
	anim->is_playing = false;
	anim->last_frame_time = 0;
	anim->num_frames = frames;
	anim->frames = ft_calloc(frames, sizeof(t_image *));
	if (!anim->frames)
		ft_error_game("Failed to allocate memory for animation frames", game);
	i = -1;
	while (++i < frames)
		load_animation_frame(game, anim, i, path);
}

void	init_shotgun_animation(t_game *game)
{
	init_weapon_animation(game,
		&game->shotgun_anim,
		SHOTGUN_ANIM_PATH,
		SHOTGUN_FRAMES);
}

void	init_pistol_animation(t_game *game)
{
	init_weapon_animation(game,
		&game->pistol_anim,
		PISTOL_ANIM_PATH,
		PISTOL_FRAMES);
}

void	init_punch_animation(t_game *game)
{
	init_weapon_animation(game,
		&game->punch_anim,
		PUNCH_ANIM_PATH,
		PUNCH_FRAMES);
}

void	init_weapons(t_game *game)
{
	init_weapon_texture(game, &game->pistol, PISTOL_PATH);
	init_weapon_texture(game, &game->shotgun, SHOTGUN_PATH);
	init_weapon_texture(game, &game->punch, PUNCH_PATH);
	init_shotgun_animation(game);
	init_pistol_animation(game);
	init_punch_animation(game);
}
