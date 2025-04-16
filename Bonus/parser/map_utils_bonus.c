/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:49:33 by wabolles          #+#    #+#             */
/*   Updated: 2025/04/13 21:44:16 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

char	*remove_symbol(char *input_string, char symbol)
{
	size_t	length;
	char	*new_string;
	size_t	j;
	size_t	i;

	length = ft_strlen(input_string);
	new_string = (char *)malloc(length + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	j = 0;
	while (i < length)
	{
		if (input_string[i] != symbol)
			new_string[j++] = input_string[i];
		i++;
	}
	new_string[j] = '\0';
	return (new_string);
}

int	array_size(char **array)
{
	int	count;

	count = 0;
	while (array[count])
		count++;
	return (count);
}

bool	is_one_or_space(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (false);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\f' && str[i] != '\n'
			&& str[i] != '\r' && str[i] != '\t' && str[i] != '\v')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	error_color(char **rgb, t_map *map, int j)
{
	int	i;

	i = 0;
	while (rgb[j][i])
	{
		if (!ft_isdigit(rgb[j][i]))
			ft_error_map_array("Color params only numbers", map, rgb);
		if (i >= 3)
			ft_error_map_array("Numbers color no more 3", map, rgb);
		i++;
	}
	return (true);
}

bool	check_all_params(t_map *map)
{
	if (!map->ea || !map->we || !map->so || !map->no || !map->floor
		|| !map->ceiling)
		return (false);
	return (true);
}
