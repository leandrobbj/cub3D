/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 18:10:09 by lbraga            #+#    #+#             */
/*   Updated: 2026/10/23 17:15:24 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_down(int key, t_game *g)
{
	if (key == KEY_ESC)
		exit_game(g, NULL);
	if (key == KEY_W)
		g->input.key_w = true;
	if (key == KEY_S)
		g->input.key_s = true;
	if (key == KEY_UP)
		g->input.key_up = true;
	if (key == KEY_DOWN)
		g->input.key_down = true;
	if (key == KEY_A)
		g->input.strafe_left = true;
	if (key == KEY_D)
		g->input.strafe_right = true;
	if (key == KEY_LEFT)
		g->input.rotate_left = true;
	if (key == KEY_RIGHT)
		g->input.rotate_right = true;
	if (key == KEY_M)
		g->input.show_map = !g->input.show_map;
	if (key == KEY_F)
		g->input.show_flat = !g->input.show_flat;
	if (key == KEY_SHIFT_L)
		g->input.key_run = true;
	return (0);
}

int	key_up(int key, t_game *g)
{
	if (key == KEY_W)
		g->input.key_w = false;
	if (key == KEY_S)
		g->input.key_s = false;
	if (key == KEY_UP)
		g->input.key_up = false;
	if (key == KEY_DOWN)
		g->input.key_down = false;
	if (key == KEY_A)
		g->input.strafe_left = false;
	if (key == KEY_D)
		g->input.strafe_right = false;
	if (key == KEY_LEFT)
		g->input.rotate_left = false;
	if (key == KEY_RIGHT)
		g->input.rotate_right = false;
	if (key == KEY_SHIFT_L)
		g->input.key_run = false;
	return (0);
}

int	draw_loop(t_game *g)
{
	t_dda	d;
	int		x;

	x = 0;
	move_player(g);
	d.cam_x = -1.0;
	d.cam_step = 2.0 / WIDTH;
	while (x < WIDTH)
	{
		init_dda(&d, &g->player);
		calc_step(&d, g->player.pos_x, g->player.pos_y);
		exec_dda(&d, g->map);
		set_texture(&d, &g->player);
		calc_line(&d);
		draw_line(g, &d, x);
		d.cam_x += d.cam_step;
		x++;
	}
	if (g->input.show_map)
		draw_map(g, g->map, g->tile);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	return (0);
}

int	exit_game(t_game *g, char *str)
{
	if (g->texture[NO].img)
		mlx_destroy_image(g->mlx, g->texture[NO].img);
	if (g->texture[SO].img)
		mlx_destroy_image(g->mlx, g->texture[SO].img);
	if (g->texture[EA].img)
		mlx_destroy_image(g->mlx, g->texture[EA].img);
	if (g->texture[WE].img)
		mlx_destroy_image(g->mlx, g->texture[WE].img);
	if (g->img)
		mlx_destroy_image(g->mlx, g->img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
		mlx_destroy_display(g->mlx);
	free(g->mlx);
	free_config(&g->setup);
	if (str)
	{
		ft_putendl_fd(str, STDOUT_FILENO);
		exit(1);
	}
	ft_putendl_fd("cub3D closed x", STDOUT_FILENO);
	exit (0);
}

int	close_window(t_game *g)
{
	exit_game(g, NULL);
	return (0);
}
