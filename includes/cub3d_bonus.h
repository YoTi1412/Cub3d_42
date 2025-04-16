/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:55:53 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/13 20:39:56 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include "../mlx/mlx.h"
# include <assert.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define PINK 0xffc0cb
# define BLUE 0x0100fa
# define GREEN 0x00fa01
# define REDD 0xfa0100
# define YELLOW 0xffff00
# define FL 0xa9a9a9
# define CEAL 0xf5f5f5
# define WHITE 0xffffff
# define BLACK 0x000000
# define BLACK_ 0x010001

# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.025

# define SCREEN_W 1280
# define SCREEN_H 720

# define TEXWIDTH 64
# define TEXHEIGHT 64

# define MINI_CUBE 15
# define MAP_RADIUS 100
# define MAP_OFFSET 75

# define WEAPON_WIDTH 441
# define WEAPON_HEIGHT 248

# define DISTANCE 0.2

# define KEY_MOUSE_LEFT 1
# define KEY_MOUSE_RIGHT 3
# define MOUSE_SUP 4
# define MOUSE_SDOWN 5

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPACE 32
# define KP 02
# define KR 03

# define ON_DESTROY 17

# define DOOR_PATH "textures/walls/door_b.xpm"
# define NUM_WEAPONS 3
# define SHOTGUN_PATH "textures/weapons/Shotgun/shotgun1.xpm"
# define PISTOL_PATH "textures/weapons/pistol/pistol1.xpm"
# define PUNCH_PATH "textures/weapons/punch/punch1.xpm"
# define SHOTGUN_ANIM_PATH "textures/weapons/Shotgun/shotgun"
# define PISTOL_ANIM_PATH "textures/weapons/pistol/pistol"
# define PUNCH_ANIM_PATH "textures/weapons/punch/punch"
# define SHOTGUN_FRAMES 5
# define PUNCH_FRAMES 3
# define PISTOL_FRAMES 5
# define ANIM_FRAME_DELAY 50

typedef enum e_weapon
{
	SHOTGUN = 0,
	PISTOL,
	PUNCH
}	t_weapon;

typedef struct s_map
{
	t_dll			*data;
	char			**map;
	int				start_map;
	int				height;
	int				width;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*floor;
	char			*ceiling;
	unsigned int	color_floor;
	unsigned int	color_ceiling;
}	t_map;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
	int		width;
	int		height;
}	t_image;

typedef struct s_player
{
	char	direction;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_raycast
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_raycast;

typedef struct s_pressed
{
	bool	left;
	bool	right;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	space;
}	t_pressed;

typedef struct s_weapon_anim
{
	t_image		**frames;
	int			num_frames;
	int			current_frame;
	bool		is_playing;
	long long	last_frame_time;
}	t_weapon_anim;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_line_vars
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	t_point	current;
}	t_line_vars;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	t_map			*map;
	t_player		player;
	t_raycast		rc;
	t_image			*bg;
	t_pressed		pressed;
	t_image			*no_img;
	t_image			*so_img;
	t_image			*we_img;
	t_image			*ea_img;
	int				type_weapon;
	t_image			*pistol;
	t_image			*shotgun;
	t_image			*punch;
	t_image			*current_weapon;
	t_weapon_anim	shotgun_anim;
	t_weapon_anim	pistol_anim;
	t_weapon_anim	punch_anim;
	t_image			*door;
	int				door_x;
	int				door_y;
	bool			door_open;
	char			*music;
	pid_t			pid;
}	t_game;

/* errors */
void		ft_error_game(char *msg, t_game *game);
void		ft_error_map(char *msg, t_map *map);
void		ft_error_list(char *msg, t_dll *data);
void		ft_error_map_array(char *msg, t_map *map, char **array);
int			exit_game(t_game *game);
void		free_map(t_map *map);
void		free_game(t_game *game);
void		free_image(void *mlx, t_image *image);

/* game */
void		init_game(t_map *map);
int			key_action(int key, t_game *game);
int			key_release(int key, t_game *game);
bool		execute_moves(t_game *game);
void		rotate_right(t_game *game);
void		rotate_left(t_game *game);

/* parser */
void		check_command_line_args(int argc, char **argv);
t_dll		*check_start_map(t_map *map, t_dll *data);
t_dll		*check_last_map(t_dll *dataList);
t_map		*check_map(char *path);
char		*remove_symbol(char *input_string, char symbol);
int			array_size(char **array);
bool		is_one_or_space(const char *str);
bool		error_color(char **rgb, t_map *map, int j);
bool		check_all_params(t_map *map);
void		valid_symbols(t_map *map);
void		check_map_row(t_map *map, const char *row, int *player_count);
bool		valid_direction(char c);
bool		valid_char(char c);
void		validate_map(t_map *map);
void		check_parameter(t_map *map, char **params);

/* raycasting */
void		ray_direction_calculate(t_game *game, int x);
void		calculate_step_and_dist(t_game *game);
void		set_ray_steps(t_game *game);
void		calculate_wall_parameters(t_game *game);
void		calculate_texture_coordinates(t_game *game);
int			render(t_game *game);
void		add_plane_char(t_game *game);
int			get_texture_pixel(t_image *texture, int tex_x, int tex_y);
t_image		*get_texture_directions(t_game *game);
void		ft_mlx_pixel_put(t_image *image, int x, int y, int color);
void		init_texture(t_game *game, t_image **texture, \
				char *path_texture, int size_texture);

/* bonus */
void		init_textures(t_game *game);
void		open_door(t_game *game);
void		render_door(t_game *game, int x, int y);
void		update_status_door(t_game *game);
void		draw_minimap(t_game *game, t_map *map, t_player *player);
int			define_color(int type);
void		check_map_row_door(t_map *map, const char *row, \
				int *player_count, int row_index);
void		valid_door(t_map *map, const char *row, int col, int row_index);
void		render_weapon(t_game *game);
void		init_event_mouse(t_game *game);
int			mouse_move(int x, int y, t_game *game);
void		scroll_down(t_game *game);
void		scroll_up(t_game *game);
int			mouse_hook(int keycode, int x, int y, t_game *game);
bool		is_inside_minimap_circle(int x, int y, int radius);
void		init_shotgun_animation(t_game *game);
void		init_punch_animation(t_game *game);
void		update_weapon_animation(t_game *game);
int			get_max_row_width(char **map);
int			get_row_count(char **map);
void		init_params(t_map *map, t_dll *data);
void		handle_weapon_fire(t_game *game, long long current_ms);
int			mouse_hook(int keycode, int x, int y, t_game *game);
void		init_walls(t_game *game);
void		load_weapon_texture(t_game *game, t_image **texture, char *path);
void		init_weapon_texture(t_game *game, t_image **texture, char *path);
char		*generate_frame_filename(const char *path, int i);
void		load_animation_frame(t_game *game, t_weapon_anim *anim, \
				int i, const char *path);
void		init_weapons(t_game *game);
void		init_punch_animation(t_game *game);
void		init_pistol_animation(t_game *game);
void		init_shotgun_animation(t_game *game);
void		init_weapon_animation(t_game *game, t_weapon_anim *anim, \
				const char *path, int frames);
void		update_anim(t_weapon_anim *anim, long long current_ms);
void		update_weapon_animation(t_game *game);
void		init_textures(t_game *game);
void		draw_minimap_wall_pixel(int wall_x, int wall_y, \
				t_image *bg, int bg_color);
void		draw_minimap_walls(t_game *game, t_map *map, t_player *player);
void		draw_rays(t_game *game);
void		draw_minimap_border_circle(int radius, t_image *bg, \
				int border_color, int thickness);
bool		is_inside_minimap_circle(int x, int y, int radius);
void		draw_line(t_image *bg, t_point start, t_point end, int color);
void		init_line_vars(t_line_vars *vars, t_point start, t_point end);

#endif
