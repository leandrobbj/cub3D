/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:17:14 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/23 17:11:51 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static int	parse_component(char **s)
{
	int	value;
	int	digits;

	while (**s == ' ')
		(*s)++;
	value = 0;
	digits = 0;
	while (ft_isdigit(**s))
	{
		value = value * 10 + (**s - '0');
		if (value > 255)
			return (-1);
		digits++;
		(*s)++;
	}
	while (**s == ' ')
		(*s)++;
	if (digits == 0)
		return (-1);
	return (value);
}

static int	parse_rgb(char *s, int *color)
{
	int	rgb[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = parse_component(&s);
		if (rgb[i] < 0)
			return (1);
		if (i < 2)
		{
			if (*s != ',')
				return (1);
			s++;
		}
		i++;
	}
	if (*s)
		return (1);
	*color = rgb_to_int(rgb[0], rgb[1], rgb[2]);
	return (0);
}

t_error	parse_color(char *line, t_setup *cfg)
{
	int	*slot;
	int	color;

	if (line[0] == 'F')
		slot = &cfg->color_f;
	else
		slot = &cfg->color_c;
	if (*slot != -1)
		return (ERR_DUP_ELEMENT);
	if (parse_rgb(line + 1, &color))
		return (ERR_COLOR);
	*slot = color;
	return (OK);
}
