/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:01:16 by wabolles          #+#    #+#             */
/*   Updated: 2025/04/13 21:44:38 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static bool	is_wall_error(char **map, int x, int y)
{
	if (y - 1 < 0 || x - 1 < 0 || !map[y - 1] || !map[y + 1])
		return (true);
	if ((int)ft_strlen(map[y - 1]) <= x || (int)ft_strlen(map[y + 1]) <= x || x
		- 1 < 0 || x + 1 >= (int)ft_strlen(map[y]))
		return (true);
	if (map[y][x + 1] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' '
		|| map[y - 1][x] == ' ')
		return (true);
	return (false);
}

static bool	check_walls(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] == '0' || valid_direction(map[y][x]))
				&& is_wall_error(map, x, y))
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

static bool	check_corners(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || valid_direction(map[y][x]))
			{
				if (!map[y - 1][x + 1] || !map[y + 1][x + 1] || map[y - 1][x
					- 1] == ' ' || map[y + 1][x - 1] == ' ' || map[y - 1][x
					+ 1] == ' ' || map[y + 1][x + 1] == ' ')
					return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

void	validate_map(t_map *map)
{
	valid_symbols(map);
	if (check_walls(map->map))
		ft_error_map("Invalid wall structure or internal spaces", map);
	if (check_corners(map->map))
		ft_error_map("Empty corners found. '0' must be surrounded by walls",
			map);
}

int	define_color(int type)
{
	if (type == 'D')
		return (0x3b2105);
	else if (type == 'O')
		return (0x3a6616);
	else
		return (0x000000);
}
