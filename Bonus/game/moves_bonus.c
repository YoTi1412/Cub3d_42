/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:17:28 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 16:06:51 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	move_front(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_pos_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (game->map->map[(int)(new_pos_x + DISTANCE
			* game->player.dir_x)][(int)game->player.pos_y] == '0'
		|| game->map->map[(int)(new_pos_x + DISTANCE
			* game->player.dir_x)][(int)game->player.pos_y] == 'O')
		game->player.pos_x = new_pos_x;
	if (game->map->map[(int)game->player.pos_x][(int)(new_pos_y + DISTANCE
		* game->player.dir_y)] == '0'
		|| game->map->map[(int)game->player.pos_x][(int)(new_pos_y + DISTANCE
			* game->player.dir_y)] == 'O')
		game->player.pos_y = new_pos_y;
}

void	move_back(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_pos_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (game->map->map[(int)(new_pos_x - DISTANCE
			* game->player.dir_x)][(int)game->player.pos_y] == '0'
		|| game->map->map[(int)(new_pos_x - DISTANCE
			* game->player.dir_x)][(int)game->player.pos_y] == 'O')
		game->player.pos_x = new_pos_x;
	if (game->map->map[(int)game->player.pos_x][(int)(new_pos_y - DISTANCE
		* game->player.dir_y)] == '0'
		|| game->map->map[(int)game->player.pos_x][(int)(new_pos_y - DISTANCE
			* game->player.dir_y)] == 'O')
		game->player.pos_y = new_pos_y;
}

void	move_left(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
	new_pos_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
	if (game->map->map[(int)(new_pos_x - DISTANCE
			* game->player.plane_x)][(int)game->player.pos_y] == '0'
		|| game->map->map[(int)(new_pos_x - DISTANCE
			* game->player.plane_x)][(int)game->player.pos_y] == 'O')
		game->player.pos_x = new_pos_x;
	if (game->map->map[(int)game->player.pos_x][(int)(new_pos_y - DISTANCE
		* game->player.plane_y)] == '0'
		|| game->map->map[(int)game->player.pos_x][(int)(new_pos_y - DISTANCE
			* game->player.plane_y)] == 'O')
		game->player.pos_y = new_pos_y;
}

void	move_right(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
	new_pos_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
	if (game->map->map[(int)(new_pos_x + DISTANCE
			* game->player.plane_x)][(int)game->player.pos_y] == '0'
		|| game->map->map[(int)(new_pos_x + DISTANCE
			* game->player.plane_x)][(int)game->player.pos_y] == 'O')
		game->player.pos_x = new_pos_x;
	if (game->map->map[(int)game->player.pos_x][(int)(new_pos_y + DISTANCE
		* game->player.plane_y)] == '0'
		|| game->map->map[(int)game->player.pos_x][(int)(new_pos_y + DISTANCE
			* game->player.plane_y)] == 'O')
		game->player.pos_y = new_pos_y;
}

bool	execute_moves(t_game *game)
{
	if (game->pressed.w)
		move_front(game);
	if (game->pressed.s)
		move_back(game);
	if (game->pressed.a)
		move_left(game);
	if (game->pressed.d)
		move_right(game);
	if (game->pressed.left)
		rotate_left(game);
	if (game->pressed.right)
		rotate_right(game);
	if (game->pressed.space)
		open_door(game);
	return (true);
}
