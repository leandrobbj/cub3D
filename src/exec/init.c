/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 18:01:46 by lbraga            #+#    #+#             */
/*   Updated: 2026/10/26 20:30:17 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_game(g, "error: mlx_init failed");
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "window 1");
	if (!g->win)
		exit_game(g, "error: mlx_new_window failed");
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->img)
		exit_game(g, "error: mlx_new_image failed");
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	if (!g->data)
		exit_game(g, "error: mlx_get_data_addr failed");
}

static void	load_texture(t_game *g, t_texture *t, char *file)
{
	t->img = mlx_xpm_file_to_image(g->mlx, file, &t->width, &t->height);
	if (!t->img)
		exit_game(g, "error: fail to load XPM");
	t->data = mlx_get_data_addr(t->img, &t->bpp, &t->size_line, &t->endian);
	if (!t->data)
		exit_game(g, "error: fail to get data address");
}

static void	init_coordinates(t_player *p, t_setup *set)
{
	p->pln_x = 0.0;
	p->pln_y = 0.0;
	p->fov_factor = tan((FOV * M_PI / 180.0) / 2.0);
	if (set->dir == 'N')
	{
		p->dir = M_PI * 3 / 2;
		p->pln_x = p->fov_factor;
	}
	else if (set->dir == 'S')
	{
		p->dir = M_PI / 2;
		p->pln_x = -p->fov_factor;
	}
	else if (set->dir == 'E')
	{
		p->dir = M_PI * 2;
		p->pln_y = p->fov_factor;
	}
	else if (set->dir == 'W')
	{
		p->dir = M_PI;
		p->pln_y = -p->fov_factor;
	}
	p->dir_x = cos(p->dir);
	p->dir_y = sin(p->dir);
}

static int	get_tile_size(t_setup *s)
{
	int		x;
	int		y;
	t_tile	t;

	y = 0;
	t.map_w = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
			x++;
		if (x > t.map_w)
			t.map_w = x;
		y++;
	}
	t.map_h = y;
	t.width = ((WIDTH * MAP) / 100) / t.map_w;
	t.height = ((HEIGHT * MAP) / 100) / t.map_h;
	if (t.width < t.height)
		t.size = t.width;
	else
		t.size = t.height;
	if (t.size < 1)
		t.size = 1;
	return (t.size);
}

void	start_cub3d(t_game *g)
{
	init_mlx(g);
	load_texture(g, &g->texture[NO], g->setup.tex_n);
	load_texture(g, &g->texture[SO], g->setup.tex_s);
	load_texture(g, &g->texture[EA], g->setup.tex_e);
	load_texture(g, &g->texture[WE], g->setup.tex_w);
	g->map = g->setup.map;
	g->tile = get_tile_size(&g->setup);
	g->player.pos_x = g->setup.pos_x + 0.5;
	g->player.pos_y = g->setup.pos_y + 0.5;
	init_coordinates(&g->player, &g->setup);
	mlx_hook(g->win, ON_KEYDOWN, 1L << 0, key_down, g);
	mlx_hook(g->win, ON_KEYUP, 1L << 1, key_up, g);
	mlx_loop_hook(g->mlx, draw_loop, g);
	mlx_hook(g->win, ON_DESTROY, 0L, close_window, g);
	mlx_loop(g->mlx);
}
