/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:28:12 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:47:27 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static t_image	*get_type_weapon(t_game *game)
{
	t_weapon_anim	*anim;

	if (game->type_weapon == SHOTGUN)
	{
		anim = &game->shotgun_anim;
		if (anim->is_playing)
			return (anim->frames[anim->current_frame]);
		return (game->shotgun);
	}
	else if (game->type_weapon == PISTOL)
	{
		anim = &game->pistol_anim;
		if (anim->is_playing)
			return (anim->frames[anim->current_frame]);
		return (game->pistol);
	}
	anim = &game->punch_anim;
	if (anim->is_playing)
		return (anim->frames[anim->current_frame]);
	return (game->punch);
}

static void	draw_weapon(t_game *game, int draw_x_start, int draw_y_start)
{
	unsigned int	color;
	int				x;
	int				y;

	x = 0;
	while (x < WEAPON_WIDTH)
	{
		y = 0;
		while (y < WEAPON_HEIGHT)
		{
			color = get_texture_pixel(game->current_weapon, x, y);
			if (color != 0xFF000000)
			{
				ft_mlx_pixel_put(game->bg, draw_x_start + x, draw_y_start + y,
					color);
			}
			y++;
		}
		x++;
	}
}

void	render_weapon(t_game *game)
{
	int	draw_x_start;
	int	draw_y_start;

	game->current_weapon = get_type_weapon(game);
	update_weapon_animation(game);
	draw_x_start = SCREEN_W * 0.90 - WEAPON_WIDTH;
	draw_y_start = SCREEN_H - WEAPON_HEIGHT;
	if (draw_x_start < 0)
		draw_x_start = 0;
	if (draw_y_start < 0)
		draw_y_start = 0;
	draw_weapon(game, draw_x_start, draw_y_start);
}
