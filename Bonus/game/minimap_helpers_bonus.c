/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helpers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:37:32 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/11 12:46:53 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_line_vars(t_line_vars *vars, t_point start, t_point end)
{
	vars->dx = abs(end.x - start.x);
	vars->dy = abs(end.y - start.y);
	vars->sx = (start.x < end.x) * 2 - 1;
	vars->sy = (start.y < end.y) * 2 - 1;
	vars->err = vars->dx - vars->dy;
	vars->current = start;
}

void	draw_line(t_image *bg, t_point start, t_point end, int color)
{
	t_line_vars	vars;

	init_line_vars(&vars, start, end);
	while (1)
	{
		if (is_inside_minimap_circle(vars.current.x - MAP_OFFSET, \
			vars.current.y - MAP_OFFSET, MAP_RADIUS))
			ft_mlx_pixel_put(bg, vars.current.x, vars.current.y, color);
		if (vars.current.x == end.x && vars.current.y == end.y)
			break ;
		vars.e2 = 2 * vars.err;
		if (vars.e2 > -vars.dy)
		{
			vars.err -= vars.dy;
			vars.current.x += vars.sx;
		}
		if (vars.e2 < vars.dx)
		{
			vars.err += vars.dx;
			vars.current.y += vars.sy;
		}
	}
}

bool	is_inside_minimap_circle(int x, int y, int radius)
{
	int	dx;
	int	dy;

	dx = x - radius;
	dy = y - radius;
	return (dx * dx + dy * dy <= radius * radius);
}

static bool	is_minimap_edge_pixel(int x, int y, int radius, int thickness)
{
	int	i;
	int	j;

	j = -thickness;
	while (j <= thickness)
	{
		i = -thickness;
		while (i <= thickness)
		{
			if (!is_inside_minimap_circle(x + i, y + j, radius))
				return (true);
			i++;
		}
		j++;
	}
	return (false);
}

void	draw_minimap_border_circle(int radius, t_image *bg, \
	int border_color, int thickness)
{
	int	x;
	int	y;
	int	diameter;

	diameter = radius * 2;
	y = 0;
	while (y < diameter)
	{
		x = 0;
		while (x < diameter)
		{
			if (is_inside_minimap_circle(x, y, radius))
			{
				if (is_minimap_edge_pixel(x, y, radius, thickness))
					ft_mlx_pixel_put(bg, MAP_OFFSET + x, MAP_OFFSET \
							+ y, border_color);
			}
			x++;
		}
		y++;
	}
}
