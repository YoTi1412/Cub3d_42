/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:34:34 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/07 22:35:56 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	render_floor_and_ceiling(t_game *game)
{
	unsigned int	*dst;
	int				i;

	dst = (unsigned int *)game->bg->addr;
	i = SCREEN_W * SCREEN_H / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->color_ceiling;
	i = SCREEN_W * SCREEN_H / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->color_floor;
}

static void	render_walls(t_game *game, int x, int y)
{
	game->rc.tex_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
	game->rc.tex_pos += game->rc.step;
	game->rc.color = get_texture_pixel(get_texture_directions(game),
			game->rc.tex_x, game->rc.tex_y);
	ft_mlx_pixel_put(game->bg, x, y, game->rc.color);
}

int	render(t_game *game)
{
	int	y;
	int	x;

	x = -1;
	render_floor_and_ceiling(game);
	while (++x < SCREEN_W)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
		{
			render_walls(game, x, y);
		}
	}
	execute_moves(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->bg->img, 0, 0);
	return (0);
}
