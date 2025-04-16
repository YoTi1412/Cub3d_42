/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:52:55 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/09 16:03:55 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static double	calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

static void	toggle_door(t_game *game, int x, int y)
{
	double	distance;

	distance = calculate_distance(game->player.pos_x, game->player.pos_y, x, y);
	if (distance < 2)
	{
		game->door_x = x;
		game->door_y = y;
		if (game->map->map[x][y] == 'D')
		{
			game->door_open = 1;
		}
		else if (game->map->map[x][y] == 'O')
		{
			game->door_open = false;
		}
	}
}

void	update_status_door(t_game *game)
{
	int	door_x;
	int	door_y;

	door_x = game->door_x;
	door_y = game->door_y;
	if (game->door_open)
	{
		if (game->map->map[door_x][door_y] == 'D')
			game->map->map[door_x][door_y] = 'O';
	}
	else
	{
		if (game->map->map[door_x][door_y] == 'O')
			game->map->map[door_x][door_y] = 'D';
	}
}

void	open_door(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = (int)game->player.pos_x;
	player_y = (int)game->player.pos_y;
	if (game->map->map[player_x + 1][player_y] == 'D'
		|| game->map->map[player_x + 1][player_y] == 'O')
		toggle_door(game, player_x + 1, player_y);
	else if (game->map->map[player_x - 1][player_y] == 'D'
		|| game->map->map[player_x - 1][player_y] == 'O')
		toggle_door(game, player_x - 1, player_y);
	else if (game->map->map[player_x][player_y + 1] == 'D'
		|| game->map->map[player_x][player_y + 1] == 'O')
		toggle_door(game, player_x, player_y + 1);
	else if (game->map->map[player_x][player_y - 1] == 'D'
		|| game->map->map[player_x][player_y - 1] == 'O')
		toggle_door(game, player_x, player_y - 1);
	game->pressed.space = false;
}
