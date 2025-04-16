/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:34:34 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:49:58 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
	if (game->map->map[game->rc.map_x][game->rc.map_y] == 'D')
	{
		render_door(game, x, y);
	}
	else
	{
		game->rc.tex_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
		game->rc.tex_pos += game->rc.step;
		game->rc.color = get_texture_pixel(get_texture_directions(game),
				game->rc.tex_x, game->rc.tex_y);
		ft_mlx_pixel_put(game->bg, x, y, game->rc.color);
	}
}

static void	draw_crosshair(t_game *game)
{
	int	center_x;
	int	center_y;
	int	x;
	int	y;
	int	crosshair_size;

	center_x = SCREEN_W / 2;
	center_y = SCREEN_H / 2;
	crosshair_size = 12;
	x = center_x - crosshair_size;
	while (x <= center_x + crosshair_size)
	{
		ft_mlx_pixel_put(game->bg, x, center_y, GREEN);
		x++;
	}
	y = center_y - crosshair_size;
	while (y <= center_y + crosshair_size)
	{
		ft_mlx_pixel_put(game->bg, center_x, y, GREEN);
		y++;
	}
}

void	render_door(t_game *game, int x, int y)
{
	int	texture_x;
	int	texture_y;
	int	color;

	texture_x = (int)(game->rc.wall_x * TEXWIDTH);
	texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
	game->rc.tex_pos += game->rc.step;
	color = get_texture_pixel(game->door, texture_x, texture_y);
	ft_mlx_pixel_put(game->bg, x, y, color);
}

int	render(t_game *game)
{
	int	y;
	int	x;

	x = -1;
	render_floor_and_ceiling(game);
	update_status_door(game);
	while (++x < SCREEN_W)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
			render_walls(game, x, y);
	}
	render_weapon(game);
	draw_minimap(game, game->map, &game->player);
	draw_crosshair(game);
	execute_moves(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->bg->img, 0, 0);
	return (0);
}
