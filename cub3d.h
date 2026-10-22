/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 17:53:13 by lbraga            #+#    #+#             */
/*   Updated: 2026/10/22 15:30:01 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "minilibx-linux/mlx.h"
# include "src/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define M_PI 3.14159265358979323846	// PI = 180
# define WIDTH 1200
# define HEIGHT 900
# define FOV 66.8		// 4:3 = 66.8 / 16:9 82,6
# define ROTATE 0.05	// 0.03 - 0.9 MAX
# define SPEED 0.03		// 0.05 - 0.9 MAX
# define MAP 50			// SIZE MAP PERCENTAGE
# define MARGIN 0.2 	// 0.5 MAX

enum e_colors
{
	RED = 0xFF0000,
	GRE = 0x00FF00,
	BLU = 0x0000FF,
	CIA = 0x00FFFF,
	MAG = 0xFF00FF,
	YEL = 0xFFFF00,
	WALL1 = BLU,
	WALL2 = MAG,
	TILE1 = RED,
	TILE2 = MAG,
	RAY = GRE
};

enum e_keys	// xev
{
	KEY_W = 0x77,
	KEY_A = 0x61,
	KEY_S = 0x73,
	KEY_D = 0x64,
	KEY_UP = 0xFF52,
	KEY_DOWN = 0xFF54,
	KEY_LEFT = 0xFF51,
	KEY_RIGHT = 0xFF53,
	KEY_ESC = 0xFF1B,
	KEY_M = 0x6d,
	KEY_F = 0x66,
	KEY_SHIFT_L = 0xffe1
};

enum e_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_directions
{
	NO = 0,
	SO = 1,
	EA = 2,
	WE = 3,
	VERTI,
	HORIZ
};

typedef enum e_error
{
	OK,
	ERR_ARGS,
	ERR_EXT,
	ERR_OPEN,
	ERR_READ,
	ERR_EMPTY,
	ERR_NO_MAP,
//	ERR_MAP_SPACES,
	ERR_MAP_CHAR,
	ERR_MULTIPLE_OR_NO_PLAYER,
	ERR_MAP_OPEN,
	ERR_MAP_NOT_LAST,
	ERR_ELEMENT,
	ERR_MISSING_ELEMENT,
	ERR_DUP_ELEMENT,
	ERR_TEXTURE,
	ERR_COLOR,
	ERR_MALLOC
}	t_error;

typedef struct s_line
{
	int	x;
	int	y;
	int	size;
	int	end;
}	t_line;

typedef struct s_tile
{
	int	map_w;
	int	map_h;
	int	map_s;
	int	width;
	int	height;
	int	size;
}	t_tile;

typedef struct s_dda
{
	double	cam_x;		// Camera position in x
	double	cam_step;
	int		map_x;		// Position in map matrix
	int		map_y;
	double	dir_x;		// Direction of axis
	double	dir_y;
	double	delta_x;	// Distance unit to next grid
	double	delta_y;
	int		step_x;		// Step direction
	int		step_y;
	double	dist_x;		// Distance to colision
	double	dist_y;
	int		side_hit;	// Vertical, horizontal
	double	perp_dist;
	double	offset_x;
	int		index;
	int		x;
	double	height;
	int		start;
	int		end;
}	t_dda;

typedef struct s_setup
{
	char	**map;
	int		color_c;
	int		color_f;
	char	dir;
	int		pos_x;
	int		pos_y;
	char	*tex_n;
	char	*tex_s;
	char	*tex_e;
	char	*tex_w;
}	t_setup;

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_input
{
	bool	key_w;
	bool	key_s;
	bool	key_up;
	bool	key_down;
	bool	strafe_left;
	bool	strafe_right;
	bool	rotate_left;
	bool	rotate_right;
	bool	show_map;
	bool	show_flat;
	bool	key_run;
}	t_input;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	fov_factor;
	double	pln_x;
	double	pln_y;
	double	dir;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	char		**map;
	int			tile;
	t_setup		setup;
	t_texture	texture[4];
	t_input		input;
	t_player	player;
}	t_game;

/* parsing.c */
t_error	parse_file(char *path, t_setup *cfg);
/* file.c */
int		check_extension(char *path, char *ext);
char	**read_lines(int fd);
/* map/map_parsing.c */
t_error	check_map(char **lines, int start, t_setup *cfg);
/* map/map.c */
int		is_valid_map_char(char c);
int		check_map_chars(char **lines, int start, int height);
int		find_player(char **lines, int start, int height, t_setup *cfg);
//int		map_has_content(char **lines, int start, int height);
/* map/map_grid.c */
int		build_map(char **lines, int start, int height, t_setup *cfg);
int		map_width(char **lines, int start, int height);
int		check_blank_lines(char **lines, int start);
/* map/map_closed.c */
int		check_map_closed(char **map, int width, int height);
int		is_open_cell(char **map, int x, int y, int *size);
/* elements/elements.c */
t_error	parse_elements(char **lines, int *start, t_setup *cfg);
/* elements/texture.c */
char	**get_tex_slot(t_setup *cfg, char *id);
t_error	parse_texture(char *rest, char **slot);
/* elements/color.c */
t_error	parse_color(char *line, t_setup *cfg);
/* errors.c */
int		print_error(t_error err);
/* utils.c */
void	init_config(t_setup *cfg);
void	free_config(t_setup *cfg);
void	free_lines(char **lines);

//init
void	start_cub3d(t_game *game);
//handlers
int		key_down(int key, t_game *g);
int		key_up(int key, t_game *g);
int		draw_loop(t_game *g);
int		close_window(t_game *g);
//movement
void	move_player(t_game *g);
//dda
void	init_dda(t_dda *d, t_player *p);
void	calc_step(t_dda *d, double pos_x, double pos_y);
void	exec_dda(t_dda *d, char **map);
void	set_texture(t_dda *d, t_player *p);
void	calc_line(t_dda *d);
//draw
void	put_pixel(t_game *g, int color, int x, int y);
void	put_horizontal_line(t_game *g, int color, t_line *l);
void	draw_line(t_game *g, t_dda *d, int x);
//minimap
void	draw_map(t_game *g, char **map, int tile);
bool	touch_wall(char **map, double dx, double dy);
//exit
int		exit_game(t_game *g, char *str);

#endif