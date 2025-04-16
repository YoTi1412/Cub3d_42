/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:32:31 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:48:01 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	ft_error_game(char *msg, t_game *game)
{
	free_game(game);
	ft_error_msg(msg);
}

void	ft_error_map(char *msg, t_map *map)
{
	free_map(map);
	ft_error_msg(msg);
}

void	ft_error_list(char *msg, t_dll *data)
{
	free_dll_list(data);
	ft_error_msg(msg);
}

void	ft_error_map_array(char *msg, t_map *map, char **array)
{
	clean_2(array);
	free_map(map);
	ft_error_msg(msg);
}

int	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
