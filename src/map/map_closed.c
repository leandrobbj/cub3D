/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 18:35:29 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/23 17:11:23 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_map_closed(char **map, int width, int height)
{
	int	x;
	int	y;
	int	size[2];

	size[0] = width;
	size[1] = height;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (is_open_cell(map, x, y, size))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	is_open_cell(char **map, int x, int y, int *size)
{
	int	dx;
	int	dy;
	int	nx;
	int	ny;

	if (map[y][x] != '0' && !is_player(map[y][x]))
		return (0);
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			nx = x + dx;
			ny = y + dy;
			if (nx < 0 || nx >= size[0] || ny < 0 || ny >= size[1])
				return (1);
			if (map[ny][nx] == ' ')
				return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}
