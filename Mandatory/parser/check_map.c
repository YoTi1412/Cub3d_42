/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:46:04 by wabolles          #+#    #+#             */
/*   Updated: 2025/04/13 21:40:23 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_command_line_args(int argc, char **argv)
{
	int	map_parameter_len;

	if (argc > 2)
		ft_error_msg("Too many arguments (It should be only two).");
	if (argc < 2)
		ft_error_msg("The Map file is missing.");
	map_parameter_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_parameter_len - 4], ".cub", 4))
		ft_error_msg("Map file extention is wrong (It should be .cub).");
}

t_dll	*check_start_map(t_map *map, t_dll *data)
{
	int	i;

	i = 0;
	while (data)
	{
		if (is_one_or_space(data->string))
		{
			map->start_map = i;
			return (data);
		}
		data = data->next;
		i++;
	}
	return (NULL);
}

t_dll	*check_last_map(t_dll *dataList)
{
	t_dll	*last;

	last = ft_dbl_lstlast(dataList);
	while (!ft_strcmp(last->string, "\n"))
	{
		last = last->prev;
	}
	return (last);
}

void	check_parameter(t_map *map, char **params)
{
	if (!ft_strcmp(params[0], "NO") && !map->no)
		map->no = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "SO") && !map->so)
		map->so = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "WE") && !map->we)
		map->we = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "EA") && !map->ea)
		map->ea = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "F") && !map->floor)
		map->floor = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "C") && !map->ceiling)
		map->ceiling = ft_strdup(params[1]);
	else
		ft_error_map_array("Incorrect parameters in the file", map, params);
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
