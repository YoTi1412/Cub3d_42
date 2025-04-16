/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:37:32 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:47:48 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_minimap_bg_circle(int radius, t_image *bg, int bg_color)
{
	int	x;
	int	y;
	int	minimap_diameter;

	y = -1;
	minimap_diameter = radius * 2;
	while (++y < minimap_diameter)
	{
		x = -1;
		while (++x < minimap_diameter)
		{
			if (is_inside_minimap_circle(x, y, radius))
				ft_mlx_pixel_put(bg, MAP_OFFSET + x, MAP_OFFSET + y, bg_color);
		}
	}
}

void	draw_minimap_wall_pixel(int wall_x, int wall_y, t_image *bg,
		int bg_color)
{
	int	x;
	int	y;
	int	pixel_x;
	int	pixel_y;

	y = -1;
	while (++y < MINI_CUBE)
	{
		x = -1;
		while (++x < MINI_CUBE)
		{
			pixel_x = MAP_RADIUS + wall_x + x;
			pixel_y = MAP_RADIUS + wall_y + y;
			if (is_inside_minimap_circle(pixel_x, pixel_y, MAP_RADIUS))
				ft_mlx_pixel_put(bg, pixel_x + MAP_OFFSET, pixel_y + MAP_OFFSET,
					bg_color);
		}
	}
}

void	draw_minimap_player(t_image *bg)
{
	int	x;
	int	y;

	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			if (x * x + y * y <= 3 * 3)
			{
				ft_mlx_pixel_put(bg, MAP_OFFSET + MAP_RADIUS + x, MAP_OFFSET
					+ MAP_RADIUS + y, 0xFF0000);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game, t_map *map, t_player *player)
{
	draw_minimap_bg_circle(MAP_RADIUS, game->bg, 0x06343d);
	draw_minimap_walls(game, map, player);
	draw_minimap_player(game->bg);
	draw_rays(game);
	draw_minimap_border_circle(MAP_RADIUS, game->bg, 0xFFFFFF, 4);
}
