/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:17:57 by wabolles          #+#    #+#             */
/*   Updated: 2025/04/13 21:41:02 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		|| c == 'W');
}

bool	valid_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
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
