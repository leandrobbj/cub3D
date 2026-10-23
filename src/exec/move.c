/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:42:56 by lbraga            #+#    #+#             */
/*   Updated: 2026/10/23 17:11:43 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	input_rotation(t_player *p, t_input *input)
{
	double	rotate;

	rotate = ROTATE;
	if (input->key_run == true)
		rotate *= 2;
	if (input->rotate_left)
		p->dir -= rotate;
	if (input->rotate_right)
		p->dir += rotate;
	if (p->dir > M_PI * 2)
		p->dir -= M_PI * 2;
	if (p->dir < 0)
		p->dir = M_PI * 2;
	p->dir_x = cos(p->dir);
	p->dir_y = sin(p->dir);
	p->pln_x = -p->dir_y * p->fov_factor;
	p->pln_y = p->dir_x * p->fov_factor;
}

static void	input_movement(t_game *g, double *x, double *y, double speed)
{
	t_player	*p;

	*x = 0;
	*y = 0;
	p = &g->player;
	if (g->input.key_w || g->input.key_up)
	{
		*x += p->dir_x * speed;
		*y += p->dir_y * speed;
	}
	if (g->input.key_s || g->input.key_down)
	{
		*x -= p->dir_x * speed;
		*y -= p->dir_y * speed;
	}
	if (g->input.strafe_left)
	{
		*x += p->dir_y * speed;
		*y -= p->dir_x * speed;
	}
	if (g->input.strafe_right)
	{
		*x -= p->dir_y * speed;
		*y += p->dir_x * speed;
	}
}

static bool	can_move(char **map, double x, double y) // juntar
{
	return (!touch_wall(map, x - MARGIN, y - MARGIN)
		&& !touch_wall(map, x + MARGIN, y - MARGIN)
		&& !touch_wall(map, x - MARGIN, y + MARGIN)
		&& !touch_wall(map, x + MARGIN, y + MARGIN));
}

static void	collision_movement(t_game *g, t_player *p, double x, double y)
{
	double	new_x;
	double	new_y;

	if (x == 0 && y == 0)
		return ;
	new_x = p->pos_x + x;
	new_y = p->pos_y + y;
	if (can_move(g->map, new_x, p->pos_y))
		p->pos_x = new_x;
	if (can_move(g->map, p->pos_x, new_y))
		p->pos_y = new_y;
}

void	move_player(t_game *g)
{
	double	x;
	double	y;
	double	speed;
	double	length;

	speed = SPEED;
	if (g->input.key_run == true)
		speed *= 2;
	input_rotation(&g->player, &g->input);
	input_movement(g, &x, &y, speed);
	length = sqrt((x * x) + (y * y));
	if (length > 0)
	{
		x = (x / length) * speed;
		y = (y / length) * speed;
	}
	collision_movement(g, &g->player, x, y);
}
