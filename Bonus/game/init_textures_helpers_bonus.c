/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_helpers_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:22:08 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:47:53 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_walls(t_game *game)
{
	init_texture(game, &game->so_img, game->map->so, TEXHEIGHT);
	init_texture(game, &game->no_img, game->map->no, TEXHEIGHT);
	init_texture(game, &game->we_img, game->map->we, TEXHEIGHT);
	init_texture(game, &game->ea_img, game->map->ea, TEXHEIGHT);
	init_texture(game, &game->door, DOOR_PATH, TEXWIDTH);
}

void	load_weapon_texture(t_game *game, t_image **texture, char *path)
{
	int	w;
	int	h;

	w = WEAPON_WIDTH;
	h = WEAPON_HEIGHT;
	*texture = ft_calloc(1, sizeof(t_image));
	if (!(*texture))
		ft_error_game("Failed to allocate memory for weapon texture", game);
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!(*texture)->img)
		ft_error_game("Problem with loading image", game);
	(*texture)->width = w;
	(*texture)->height = h;
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bits_per_pixel,
			&(*texture)->line_length,
			&(*texture)->endian);
	if (!(*texture)->addr)
		ft_error_game("Problem with getting image address", game);
}

void	init_weapon_texture(t_game *game, t_image **texture, char *path)
{
	load_weapon_texture(game, texture, path);
}

char	*generate_frame_filename(const char *path, int i)
{
	char	*num;
	char	*temp;
	char	*full_path;

	num = ft_itoa(i + 1);
	if (!num)
		return (NULL);
	temp = ft_strjoin(path, num);
	free(num);
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, ".xpm");
	free(temp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

void	load_animation_frame(t_game *game, t_weapon_anim *anim,
	int i, const char *path)
{
	char	*filename;
	int		w;
	int		h;

	filename = generate_frame_filename(path, i);
	if (!filename)
		ft_error_game("Failed to generate frame filename", game);
	anim->frames[i] = ft_calloc(1, sizeof(t_image));
	if (!anim->frames[i])
		ft_error_game("Failed to allocate memory for animation frame", game);
	w = WEAPON_WIDTH;
	h = WEAPON_HEIGHT;
	anim->frames[i]->img = mlx_xpm_file_to_image(game->mlx, filename, &w, &h);
	free(filename);
	if (!anim->frames[i]->img)
		ft_error_game("Problem loading animation frame", game);
	anim->frames[i]->width = w;
	anim->frames[i]->height = h;
	anim->frames[i]->addr = mlx_get_data_addr(anim->frames[i]->img,
			&anim->frames[i]->bits_per_pixel,
			&anim->frames[i]->line_length,
			&anim->frames[i]->endian);
	if (!anim->frames[i]->addr)
		ft_error_game("Problem getting animation frame address", game);
}
