/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_helpers_2_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:18:00 by wabolles          #+#    #+#             */
/*   Updated: 2025/04/13 21:44:48 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_map_row_door(t_map *map, const char *row, int *player_count,
	int row_index)
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
		valid_door(map, row, col, row_index);
		col++;
	}
}

int	get_max_row_width(char **map)
{
	int	max_width;
	int	i;
	int	current_len;

	if (!map)
		return (0);
	max_width = 0;
	i = 0;
	while (map[i])
	{
		if (map[i])
		{
			current_len = ft_strlen(map[i]);
			if (current_len > max_width)
				max_width = current_len;
		}
		i++;
	}
	return (max_width);
}

int	get_row_count(char **map)
{
	int	count;

	if (!map)
		return (0);
	count = 0;
	while (map[count])
		count++;
	return (count);
}

void	init_params(t_map *map, t_dll *data)
{
	char	**params;
	int		i;
	int		size_params;
	char	*tmp;

	i = 0;
	while (i < map->start_map)
	{
		if (ft_strcmp(data->string, "\n"))
		{
			tmp = remove_symbol(data->string, '\n');
			free(data->string);
			data->string = tmp;
			params = ft_split(data->string, ' ');
			size_params = array_size(params);
			if (size_params != 2)
				ft_error_map_array("Invalid parameter format", map, params);
			check_parameter(map, params);
			clean_2(params);
		}
		data = data->next;
		i++;
	}
}
