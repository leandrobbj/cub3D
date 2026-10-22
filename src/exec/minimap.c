/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 17:50:22 by lbraga            #+#    #+#             */
/*   Updated: 2026/10/22 13:16:18 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch_wall(char **map, double dx, double dy)
{
	int	x;
	int	y;

	x = (int)dx;
	y = (int)dy;
	if (map[y][x] == '1')
		return (true);
	return (false);
}

static void	draw_ray(t_game *g, double angle, int size)
{
	double	x;
	double	y;

	x = g->player.pos_x * size;
	y = g->player.pos_y * size;
	while (!touch_wall(g->map, x / size, y / size))
	{
		put_pixel(g, RAY, (int)x, (int)y);
		x += cos(angle);
		y += sin(angle);
	}
}

static void	draw_fov(t_game *g, int size)
{
	int		i;
	double	fov;
	double	start;

	i = 0;
	fov = FOV * M_PI / 180.0;
	start = g->player.dir - fov / 2;
	while (i < WIDTH)
	{
		draw_ray(g, start, size);
		if (g->input.show_flat == false)
		{
			draw_ray(g, start + fov, size);
			break ;
		}
		start += fov / WIDTH;
		i++;
	}
}

static void	draw_square(t_game *game, int color, t_line *l)
{
	int	i;
	int	x;

	i = 0;
	x = l->x;
	while (i < l->size)
	{
		l->x = x + i;
		put_horizontal_line(game, color, l);
		i++;
	}
}

void	draw_map(t_game *g, char **map, int size)
{
	int		x;
	int		y;
	t_line	l;

	y = 0;
	l.size = size;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			l.x = x * size;
			l.y = y * size;
			l.end = l.y + size - 1;
			if (map[y][x] == '1')
				draw_square(g, TILE1, &l);
			else
				draw_square(g, TILE2, &l);
			x++;
		}
		y++;
	}
	draw_fov(g, size);
}
