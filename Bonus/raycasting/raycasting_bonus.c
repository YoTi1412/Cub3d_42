/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:33:27 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/12 23:04:25 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	ray_direction_calculate(t_game *game, int x)
{
	game->rc.camera_x = 2 * x / (double)SCREEN_W - 1;
	game->rc.raydir_x = game->player.dir_x + game->player.plane_x
		* game->rc.camera_x;
	game->rc.raydir_y = game->player.dir_y + game->player.plane_y
		* game->rc.camera_x;
	game->rc.map_x = (int)game->player.pos_x;
	game->rc.map_y = (int)game->player.pos_y;
	game->rc.delta_dist_x = fabs(1 / game->rc.raydir_x);
	game->rc.delta_dist_y = fabs(1 / game->rc.raydir_y);
}

void	calculate_step_and_dist(t_game *game)
{
	if (game->rc.raydir_x < 0)
	{
		game->rc.step_x = -1;
		game->rc.side_dist_x = (game->player.pos_x - game->rc.map_x)
			* game->rc.delta_dist_x;
	}
	else
	{
		game->rc.step_x = 1;
		game->rc.side_dist_x = (game->rc.map_x + 1.0 - game->player.pos_x)
			* game->rc.delta_dist_x;
	}
	if (game->rc.raydir_y < 0)
	{
		game->rc.step_y = -1;
		game->rc.side_dist_y = (game->player.pos_y - game->rc.map_y)
			* game->rc.delta_dist_y;
	}
	else
	{
		game->rc.step_y = 1;
		game->rc.side_dist_y = (game->rc.map_y + 1.0 - game->player.pos_y)
			* game->rc.delta_dist_y;
	}
}

void	set_ray_steps(t_game *game)
{
	game->rc.hit = 0;
	while (game->rc.hit == 0)
	{
		if (game->rc.side_dist_x < game->rc.side_dist_y)
		{
			game->rc.side_dist_x += game->rc.delta_dist_x;
			game->rc.map_x += game->rc.step_x;
			game->rc.side = 0;
		}
		else
		{
			game->rc.side_dist_y += game->rc.delta_dist_y;
			game->rc.map_y += game->rc.step_y;
			game->rc.side = 1;
		}
		if (game->rc.map_x < 0 || game->rc.map_x >= game->map->height
			|| game->rc.map_y < 0 || game->rc.map_y >= game->map->width)
		{
			game->rc.hit = 1;
			break ;
		}
		if (game->map->map[game->rc.map_x][game->rc.map_y] == '1' ||
			game->map->map[game->rc.map_x][game->rc.map_y] == 'D')
			game->rc.hit = 1;
	}
}

void	calculate_wall_parameters(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.perp_wall_dist = (game->rc.map_x - game->player.pos_x + (1
					- game->rc.step_x) / 2) / game->rc.raydir_x + 0.0001;
	else
		game->rc.perp_wall_dist = (game->rc.map_y - game->player.pos_y + (1
					- game->rc.step_y) / 2) / game->rc.raydir_y + 0.0001;
	game->rc.line_height = (int)(SCREEN_H / game->rc.perp_wall_dist);
	game->rc.draw_start = -game->rc.line_height / 2 + SCREEN_H / 2;
	if (game->rc.draw_start < 0)
		game->rc.draw_start = 0;
	game->rc.draw_end = game->rc.line_height / 2 + SCREEN_H / 2;
	if (game->rc.draw_end >= SCREEN_H)
		game->rc.draw_end = SCREEN_H - 1;
}

void	calculate_texture_coordinates(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.wall_x = game->player.pos_y + game->rc.perp_wall_dist
			* game->rc.raydir_y;
	else
		game->rc.wall_x = game->player.pos_x + game->rc.perp_wall_dist
			* game->rc.raydir_x;
	game->rc.wall_x -= floor(game->rc.wall_x);
	game->rc.tex_x = (int)(game->rc.wall_x * (double)TEXWIDTH);
	if (game->rc.side == 0 && game->rc.raydir_x > 0)
		game->rc.tex_x = TEXWIDTH - game->rc.tex_x - 1;
	if (game->rc.side == 1 && game->rc.raydir_y < 0)
		game->rc.tex_x = TEXWIDTH - game->rc.tex_x - 1;
	game->rc.step = 1.0 * TEXHEIGHT / game->rc.line_height;
	game->rc.tex_pos = (game->rc.draw_start - SCREEN_H / 2
			+ game->rc.line_height / 2) * game->rc.step;
}
