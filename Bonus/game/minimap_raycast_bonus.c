/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_raycast_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:37:32 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 21:47:40 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	draw_ray_hitpoint(t_image *bg, int end_x, int end_y)
{
	t_point	px;

	px.y = -1;
	while (++px.y <= 1)
	{
		px.x = -1;
		while (++px.x <= 1)
		{
			if (is_inside_minimap_circle(end_x + px.x - MAP_OFFSET,
					end_y + px.y - MAP_OFFSET, MAP_RADIUS))
				ft_mlx_pixel_put(bg, end_x + px.x, end_y + px.y, 0xFF0000);
		}
	}
}

static t_point	calculate_ray_endpoint(t_game *game)
{
	t_point	end;
	double	ray_dist;
	double	hit_x;
	double	hit_y;

	if (game->rc.side == 0)
		ray_dist = (game->rc.map_x - game->player.pos_x
				+ (1 - game->rc.step_x) / 2) / game->rc.raydir_x;
	else
		ray_dist = (game->rc.map_y - game->player.pos_y
				+ (1 - game->rc.step_y) / 2) / game->rc.raydir_y;
	hit_x = game->player.pos_x + ray_dist * game->rc.raydir_x;
	hit_y = game->player.pos_y + ray_dist * game->rc.raydir_y;
	end.x = (int)((hit_y - game->player.pos_y) * MINI_CUBE
			+ MAP_OFFSET + MAP_RADIUS);
	end.y = (int)((hit_x - game->player.pos_x) * MINI_CUBE)
		+ MAP_OFFSET + MAP_RADIUS;
	return (end);
}

static void	cast_and_draw_ray(t_game *game, int x, t_point start)
{
	t_point	end;
	int		ray_color;

	ray_direction_calculate(game, x);
	calculate_step_and_dist(game);
	set_ray_steps(game);
	end = calculate_ray_endpoint(game);
	ray_color = 0x888800;
	if (x == SCREEN_W / 2)
		ray_color = 0x00FF00;
	draw_line(game->bg, start, end, ray_color);
	draw_ray_hitpoint(game->bg, end.x, end.y);
}

void	draw_rays(t_game *game)
{
	t_raycast	s_rc;
	t_point		start;
	int			x;

	s_rc = game->rc;
	start.x = MAP_OFFSET + MAP_RADIUS;
	start.y = MAP_OFFSET + MAP_RADIUS;
	x = 0;
	while (x < SCREEN_W)
	{
		if (x % 32 == 0)
			cast_and_draw_ray(game, x, start);
		x++;
	}
	game->rc = s_rc;
}

void	draw_minimap_walls(t_game *game, t_map *map, t_player *player)
{
	int	i;
	int	j;
	int	wall_x;
	int	wall_y;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->map[i][j] == '\0')
				break ;
			if (ft_strchr("1DO", map->map[i][j]))
			{
				wall_x = (j - player->pos_y) * MINI_CUBE;
				wall_y = (i - player->pos_x) * MINI_CUBE;
				draw_minimap_wall_pixel(wall_x, wall_y, game->bg,
					define_color(map->map[i][j]));
			}
		}
	}
}
