/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 17:50:22 by lbraga            #+#    #+#             */
/*   Updated: 2026/10/21 17:44:24 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *g, int color, int x, int y)
{
	unsigned int	*pixel;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	pixel = (unsigned int *)(g->data + y * g->size_line + x * (g->bpp / 8));
	*pixel = color;
}

void	put_horizontal_line(t_game *g, int color, t_line *l)
{
	int				x;
	int				y;	
	unsigned int	*pixel;

	x = l->x;
	y = l->y;
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	while (y <= l->end)
	{
		pixel = (unsigned int *)(g->data + y * g->size_line + x * (g->bpp / 8));
		*pixel = color;
		y++;
	}
}

static unsigned int	get_texture_color(t_texture *t, int x, int y)
{
	unsigned int	*pixel;

	if (x < 0)
		x = 0;
	else if (x >= t->width)
		x = t->width - 1;
	if (y < 0)
		y = 0;
	else if (y >= t->height)
		y = t->height - 1;
	pixel = (unsigned int *)(t->data + y * t->size_line + x * (t->bpp / 8));
	return (*pixel);
}

static void	draw_texture(t_game *g, t_dda *d, t_texture *tex, int x)
{
	int				tex_x;
	int				tex_y;
	double			step;
	double			pos;
	unsigned int	color;

	tex_x = d->offset_x * tex->width;
	step = tex->height / d->height;
	pos = (d->start - (HEIGHT - d->height) / 2.0 + 1.5) * step;
	while (d->start < d->end)
	{
		tex_y = pos;
		color = get_texture_color(tex, tex_x, tex_y);
		put_pixel(g, color, x, d->start);
		pos += step;
		d->start++;
	}
}

void	draw_line(t_game *g, t_dda *d, int x)
{
	t_line	l;

	l.x = x;
	l.y = 0;
	l.end = d->start - 1;
	put_horizontal_line(g, g->setup.color_c, &l);
	l.y = d->start ;
	l.end = d->end;
	if (g->input.show_flat == false)
		draw_texture(g, d, &g->texture[d->index], x);
	else if (d->side_hit == VERTI)
		put_horizontal_line(g, WALL, &l);
	else
		put_horizontal_line(g, WAL2, &l);
	l.y = d->end + 1;
	l.end = HEIGHT - 1;
	put_horizontal_line(g, g->setup.color_f, &l);
}
