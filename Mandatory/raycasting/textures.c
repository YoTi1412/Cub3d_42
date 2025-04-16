/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:10:31 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/08 13:50:54 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

	if (!texture || !texture->addr || tex_x < 0 || tex_y < 0
		|| tex_x >= TEXWIDTH || tex_y >= TEXHEIGHT)
		return (0);
	offset = tex_y * (texture->line_length / (texture->bits_per_pixel / 8))
		+ tex_x;
	pixel = (unsigned int *)(texture->addr + offset * (texture->bits_per_pixel
				/ 8));
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

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	init_texture(t_game *game, t_image **texture, char *path_texture,
	int size_texture)
{
	int	size;

	size = size_texture;
	*texture = ft_calloc(1, sizeof(t_image));
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path_texture, &size,
			&size);
	if (!(*texture)->img)
		ft_error_game("Problem with loading image", game);
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
	if (!(*texture)->addr)
		ft_error_game("Problem with getting image address", game);
}
