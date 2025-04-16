/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:10:31 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:49:55 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	add_plane_char(t_game *game)
{
	char	plane;

	plane = game->player.direction;
	if (plane == 'S')
	{
		game->player.dir_x = 1;
		game->player.plane_y = -0.66;
	}
	else if (plane == 'N')
	{
		game->player.dir_x = -1;
		game->player.plane_y = 0.66;
	}
	else if (plane == 'E')
	{
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
	}
	else if (plane == 'W')
	{
		game->player.dir_y = -1;
		game->player.plane_x = -0.66;
	}
}

int	get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	*pixel;

	if (!texture || !texture->addr || tex_x < 0 || tex_y < 0)
		return (0);
	if (tex_x >= texture->width || tex_y >= texture->height)
		return (0);
	offset = tex_y * (texture->line_length / (texture->bits_per_pixel / 8)) \
		+ tex_x;
	pixel = (unsigned int *)(texture->addr + offset * \
		(texture->bits_per_pixel / 8));
	return (*pixel);
}

t_image	*get_texture_directions(t_game *game)
{
	if (game->rc.side == 0)
	{
		if (game->rc.raydir_x > 0)
			return (game->so_img);
		else
			return (game->no_img);
	}
	else
	{
		if (game->rc.raydir_y > 0)
			return (game->ea_img);
		else
			return (game->we_img);
	}
}

void	ft_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = image->addr + (y * image->line_length + x * \
		(image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_texture(t_game *game, t_image **texture, char *path_texture, \
	int size_texture)
{
	int	width;
	int	height;

	(void)size_texture;
	*texture = ft_calloc(1, sizeof(t_image));
	width = size_texture;
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path_texture, \
		&width, &height);
	if (!(*texture)->img)
		ft_error_game("Problem with loading image", game);
	(*texture)->width = width;
	(*texture)->height = height;
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
	if (!(*texture)->addr)
		ft_error_game("Problem with getting image address", game);
}
