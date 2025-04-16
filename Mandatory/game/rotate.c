/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:22:18 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:46:46 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROTATION_SPEED)
		- game->player.dir_y * sin(-ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROTATION_SPEED) + game->player.dir_y
		* cos(-ROTATION_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-ROTATION_SPEED)
		- game->player.plane_y * sin(-ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->player.plane_y * cos(-ROTATION_SPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED)
		- game->player.dir_y * sin(ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(ROTATION_SPEED) + game->player.dir_y
		* cos(ROTATION_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED)
		- game->player.plane_y * sin(ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(ROTATION_SPEED)
		+ game->player.plane_y * cos(ROTATION_SPEED);
}
