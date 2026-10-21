/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 17:50:22 by lbraga            #+#    #+#             */
/*   Updated: 2026/10/21 17:44:22 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(t_dda *d, t_player *p)
{
	d->map_x = (int)p->pos_x;
	d->map_y = (int)p->pos_y;
	d->dir_x = p->dir_x + p->pln_x * d->cam_x;
	d->dir_y = p->dir_y + p->pln_y * d->cam_x;
	if (d->dir_x != 0)
		d->delta_x = fabs(1.0 / d->dir_x);
	else
		d->delta_x = 1e30;
	if (d->dir_y != 0)
		d->delta_y = fabs(1.0 / d->dir_y);
	else
		d->delta_y = 1e30;
}

void	calc_step(t_dda *d, double pos_x, double pos_y)
{
	if (d->dir_x < 0)
	{
		d->step_x = -1;
		d->dist_x = (pos_x - d->map_x) * d->delta_x;
	}
	else
	{
		d->step_x = 1;
		d->dist_x = (d->map_x + 1 - pos_x) * d->delta_x;
	}
	if (d->dir_y < 0)
	{
		d->step_y = -1;
		d->dist_y = (pos_y - d->map_y) * d->delta_y;
	}
	else
	{
		d->step_y = 1;
		d->dist_y = (d->map_y + 1 - pos_y) * d->delta_y;
	}
}

void	exec_dda(t_dda *d, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (d->dist_x < d->dist_y)
		{
			d->dist_x += d->delta_x;
			d->map_x += d->step_x;
			d->side_hit = VERTI;
		}
		else
		{
			d->dist_y += d->delta_y;
			d->map_y += d->step_y;
			d->side_hit = HORIZ;
		}
		if (map[d->map_y][d->map_x] == '1')
			hit = 1;
	}
}

void	set_texture(t_dda *d, t_player *p)
{
	if (d->side_hit == VERTI)
	{
		d->perp_dist = d->dist_x - d->delta_x;
		d->offset_x = p->pos_y + d->perp_dist * d->dir_y;
		d->offset_x -= floor(d->offset_x);
		d->index = WE;
		if (d->dir_x < 0)
		{
			d->offset_x = 1.0 - d->offset_x;
			d->index = EA;
		}
	}
	else
	{
		d->perp_dist = d->dist_y - d->delta_y;
		d->offset_x = p->pos_x + d->perp_dist * d->dir_x;
		d->offset_x -= floor(d->offset_x);
		d->index = SO;
		if (d->dir_y > 0)
		{
			d->offset_x = 1.0 - d->offset_x;
			d->index = NO;
		}
	}
}

void	calc_line(t_dda *d)
{
	d->height = HEIGHT / d->perp_dist;
	d->start = (HEIGHT - d->height) / 2;
	d->end = (HEIGHT + d->height) / 2;
	if (d->start < 0)
		d->start = 0;
	if (d->end >= HEIGHT)
		d->end = HEIGHT - 1;
}
