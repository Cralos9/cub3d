/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:11:47 by rumachad          #+#    #+#             */
/*   Updated: 2024/07/08 17:00:17 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "vector2D.h"
# include <assert.h>
# include <stdbool.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LARROW 65361
# define RARROW 65363

# define HEIGHT 600
# define WIDTH 800
# define FOV 90
# define SPRITE_SIZE 64
# define SPRITE_NBR 6

# define PI 3.14159265359

# define SPEED 0.02
# define ROTATION_SPEED 1

typedef struct s_cell
{
	int	x;
	int	y;
}	t_cell;

typedef struct s_player
{
	t_v2D	pos;
	t_v2D	direction;
	t_v2D	plane;
	t_v2D	movement;
	double	fov;
	double	angle;
}	t_player;

typedef struct s_map
{
	int		x;
	int		y;
	int		height;
	int		width;
	int		player_flag;
	char	**game_map;
	char	*config_map[7];
}	t_map;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_sprite
{
	t_image	img;
	int		height;
	int		width;
	int		color;
}	t_sprite;

typedef struct s_ray
{
	t_v2D	dir;
	t_v2D	delta;
	t_v2D	side_d;
	t_v2D	step;
}	t_ray;

typedef struct s_mlx
{
	void		*lib;
	void		*window;
	t_sprite	sprite[SPRITE_NBR];
	t_player	player;
	t_map		map;
	t_image		buffer;
	t_ray		ray;
	int			tex_x;
	int			side;
	double		line_height;
	double		scale;
	double		tex_pos;
	int			sprite_index;
	int			f_color;
	int			c_color;
}	t_mlx;

// Init Map/Player/Sprites
t_player	init_player(double x, double y, char tile);

//Raycast
void		ft_crane(t_mlx *mlx);
void		calculus(t_mlx *mlx, t_ray *ray);
void		draw_line(t_mlx *mlx, int x);

// Update
void		update(t_mlx *mlx, t_player *player);
bool		move_check(t_mlx *mlx, t_v2D check);
t_v2D		get_position(t_player *player, double speed);

//Render
t_image		start_image_buffer(void *lib);

// Map
void		set_map(t_map *map, t_player *player);

// Parser (MAP)
int			check_element(t_mlx *mlx, t_sprite *sprite, char *conf_line);
int			check_path(char *line);
int			check_rgb(char *line);
int			check_conf(t_mlx *mlx, char **conf_map, t_sprite *sprite);
int			color(int nbr);
int			advance_space(char *line);
int			shift_color(int *rgb);

int			map_parser(char *map_name, t_map *map);
int			calc_map_lines(int fd, char *map_name);
char		**create_full_map(int fd, char *map_name, int nbr_lines);
int			create_content_map(t_map *map, char **full_map, int after, int len);
char		*srch_set(char *line, char *set);
int			call_flood_fill(t_mlx *mlx, t_map *map);

// Image
void		pixel_put(t_image *img, int pixelX, int pixelY, int color);
int			pixel_get(t_image *img, int pixel_x, int pixel_y);
t_sprite	xpm_to_image(t_mlx *mlx, char *texture);

// Events
int			handle_key_press(int keycode, t_mlx *mlx);
int			handle_key_release(int keycode, t_player *player);

int			close_game(t_mlx *mlx, int status);
void		print_error(char *str, int status, t_mlx *mlx);

#endif