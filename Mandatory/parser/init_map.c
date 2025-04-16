/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:28:17 by wabolles          #+#    #+#             */
/*   Updated: 2025/04/13 21:40:15 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_dll	*read_map(char *path)
{
	char	*line;
	int		fd;
	t_dll	*data;

	data = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error_msg("Could not open the file, check if the path is correct!");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!data)
			data = ft_dbl_lstnew(line);
		else
			ft_dbl_lstadd_back(&data, ft_dbl_lstnew(line));
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (close(fd) == -1)
		ft_error_msg("close");
	return (data);
}

static void	validate_color_format(char *color_string, t_map *map)
{
	int	i;
	int	comma_count;	

	if (!color_string)
		ft_error_map("Color string is NULL", map);
	if (color_string[0] == ',')
		ft_error_map("Invalid color format: leading comma", map);
	i = 0;
	comma_count = 0;
	while (color_string[i])
	{
		if (color_string[i] == ',')
		{
			comma_count++;
			if (i > 0 && color_string[i - 1] == ',')
				ft_error_map("Invalid color format: consecutive commas", map);
		}
		i++;
	}
	if (i > 0 && color_string[i - 1] == ',')
		ft_error_map("Invalid color format: trailing comma", map);
	if (comma_count != 2)
		ft_error_map("Invalid color format: must have exactly three numbers",
			map);
}

static unsigned int	init_colors(char *color_string, t_map *map)
{
	char			**rgb;
	unsigned int	colors[3];
	int				i;

	i = 0;
	if (color_string != NULL)
	{
		validate_color_format(color_string, map);
		rgb = ft_split(color_string, ',');
		if (array_size(rgb) != 3)
			ft_error_map_array("Wrong color format: must have \
				exactly three numbers", map, rgb);
		while (rgb[i])
		{
			if (error_color(rgb, map, i))
			{
				colors[i] = ft_atoi(rgb[i]);
				if (colors[i] > 255)
					ft_error_map_array("Color values must be \
						between 0 and 255", map, rgb);
			}
			i++;
		}
		clean_2(rgb);
		return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
	}
	return (0);
}

static void	init_map(t_map *map, t_dll *data)
{
	t_dll	*last;
	t_dll	*head;
	int		i;

	last = check_last_map(data);
	head = check_start_map(map, data);
	init_params(map, data);
	if (!check_all_params(map))
		ft_error_map("Not all parameters are initialized", map);
	map->color_floor = init_colors(map->floor, map);
	map->color_ceiling = init_colors(map->ceiling, map);
	i = 0;
	map->height = ft_dbl_lstsize(head, last, &map->width);
	map->map = (char **)malloc((map->height + 1) * sizeof(char *));
	if (!map->map)
		ft_error_map("Failed to allocate memory for map", map);
	while (head != last->next)
	{
		map->map[i] = remove_symbol(head->string, '\n');
		i++;
		head = head->next;
	}
	map->map[i] = NULL;
}

t_map	*check_map(char *path)
{
	t_dll	*data;
	t_map	*map;

	data = read_map(path);
	if (!data)
		ft_error_msg("Error reading map");
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		ft_error_list("Failed to allocate memory for mao", data);
	map->data = data;
	init_map(map, map->data);
	validate_map(map);
	return (map);
}
