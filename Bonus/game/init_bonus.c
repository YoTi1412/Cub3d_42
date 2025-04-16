/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:28:16 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 20:39:47 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	init_mlx_window(t_game *game)
{
	int	screen_w;
	int	screen_h;

	if (SCREEN_W < 1280 || SCREEN_H < 720)
		ft_error_game("Game resolution must be at least 1280x720", game);
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error_game("Failed to initialize MLX", game);
	mlx_get_screen_size(game->mlx, &screen_w, &screen_h);
	if (SCREEN_W > screen_w || SCREEN_H > screen_h)
		ft_error_game("Game resolution exceeds monitor resolution", game);
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "CUB3D");
	if (!game->mlx_win)
		ft_error_game("Failed to create MLX window", game);
}

static void	init_background(t_game *game)
{
	game->bg = malloc(sizeof(t_image));
	if (!game->bg)
		ft_error_game("Failed to allocate memory for background", game);
	game->bg->img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	if (!game->bg->img)
		ft_error_game("Failed to create background image", game);
	game->bg->addr = mlx_get_data_addr(game->bg->img,
			&game->bg->bits_per_pixel, &game->bg->line_length,
			&game->bg->endian);
	if (!game->bg->addr)
		ft_error_game("Failed to get background image address", game);
}

static void	init_char_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map->map[++i])
	{
		j = -1;
		while (game->map->map[i][++j])
		{
			if (valid_direction(game->map->map[i][j]))
			{
				game->player.direction = game->map->map[i][j];
				game->map->map[i][j] = '0';
				game->player.pos_x = i + 0.5;
				game->player.pos_y = j + 0.5;
			}
		}
	}
}

void	init_game(t_map *map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error_map("Failed to allocate memory for game", map);
	game->map = map;
	init_mlx_window(game);
	init_textures(game);
	init_background(game);
	init_char_pos(game);
	add_plane_char(game);
	mlx_loop_hook(game->mlx, render, game);
	init_event_mouse(game);
	mlx_hook(game->mlx_win, KP, (1L << 0), key_action, game);
	mlx_hook(game->mlx_win, KR, (1L << 1), key_release, game);
	mlx_hook(game->mlx_win, ON_DESTROY, (1L << 0), exit_game, game);
	mlx_loop(game->mlx);
}
