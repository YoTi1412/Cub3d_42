/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:34:25 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:43:00 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	clean_2(map->map);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->floor)
		free(map->floor);
	if (map->ceiling)
		free(map->ceiling);
	free_dll_list(map->data);
	free(map);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
	{
		free_image(game->mlx, game->no_img);
		free_image(game->mlx, game->so_img);
		free_image(game->mlx, game->we_img);
		free_image(game->mlx, game->ea_img);
		if (game->bg)
		{
			free_image(game->mlx, game->bg);
			game->bg = NULL;
		}
		if (game->mlx_win)
		{
			mlx_destroy_window(game->mlx, game->mlx_win);
			game->mlx_win = NULL;
		}
		free(game->mlx);
	}
	free_map(game->map);
	free(game);
}

void	free_image(void *mlx, t_image *image)
{
	if (!image)
		return ;
	if (image->img)
	{
		mlx_destroy_image(mlx, image->img);
		image->img = NULL;
	}
	free(image);
}
