/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:34:25 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 16:04:23 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

void	free_weapon_animation(void *mlx, t_weapon_anim *anim)
{
	int	i;

	if (!anim || !anim->frames)
		return ;
	i = 0;
	while (i < anim->num_frames)
	{
		if (anim->frames[i])
			free_image(mlx, anim->frames[i]);
		i++;
	}
	free(anim->frames);
	anim->frames = NULL;
}

void	free_textures(t_game *game)
{
	free_image(game->mlx, game->no_img);
	free_image(game->mlx, game->so_img);
	free_image(game->mlx, game->we_img);
	free_image(game->mlx, game->ea_img);
	free_image(game->mlx, game->door);
	free_image(game->mlx, game->pistol);
	free_image(game->mlx, game->shotgun);
	free_image(game->mlx, game->punch);
	free_weapon_animation(game->mlx, &game->shotgun_anim);
	free_weapon_animation(game->mlx, &game->pistol_anim);
	free_weapon_animation(game->mlx, &game->punch_anim);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
	{
		free_textures(game);
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
