/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_helpers_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:17:57 by wabolles          #+#    #+#             */
/*   Updated: 2025/04/13 21:45:00 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	valid_symbols(t_map *map)
{
	int	row;
	int	player_count;

	row = 0;
	player_count = 0;
	while (map->map[row])
	{
		check_map_row(map, map->map[row], &player_count);
		row++;
	}
	if (player_count == 0)
		ft_error_map("Missing character on the map", map);
}

bool	valid_char(char c)
{
	return (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D');
}

bool	valid_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	valid_door(t_map *map, const char *row, int col, int row_index)
{
	bool	horizontal_walls;
	bool	vertical_walls;

	if (row[col] == 'D')
	{
		if (col == 0)
			ft_error_map("first symbol in the line", map);
		if (row[col + 1] == '\0')
			ft_error_map("last symbol in the line", map);
		if (row_index + 1 == map->height)
			ft_error_map("the door cant be in last line", map);
		horizontal_walls = (row[col - 1] == '1' && row[col + 1] == '1');
		vertical_walls = (map->map[row_index - 1][col] == '1'
				&& map->map[row_index + 1][col] == '1');
		if (!(horizontal_walls || vertical_walls))
			ft_error_map("Door 'D' is not surrounded by walls properly", map);
	}
}

void	check_map_row(t_map *map, const char *row, int *player_count)
{
	int	col;

	col = 0;
	while (row[col])
	{
		if (valid_direction(row[col]))
		{
			if (++(*player_count) > 1)
				ft_error_map("The player's position symbol is not correct"
					"the number is incorrect", map);
		}
		if (!valid_char(row[col]))
			ft_error_map("Invalid character in the map", map);
		col++;
	}
}
