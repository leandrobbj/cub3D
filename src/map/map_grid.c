/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 18:35:32 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/21 18:24:19 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*copy_row(char *line, int width)
{
	char	*row;
	int		i;

	row = malloc(sizeof(char) * (width + 1));
	if (!row)
		return (NULL);
	i = 0;
	while (line[i] && i < width)
	{
		row[i] = line[i];
		i++;
	}
	while (i < width)
		row[i++] = ' ';
	row[i] = '\0';
	return (row);
}

int	build_map(char **lines, int start, int height, t_setup *cfg)
{
	int	i;
	int	width;

	width = map_width(lines, start, height);
	cfg->map = malloc(sizeof(char *) * (height + 1));
	if (!cfg->map)
		return (0);
	i = 0;
	while (i < height)
	{
		cfg->map[i] = copy_row(lines[start + i], width);
		if (!cfg->map[i])
		{
			while (i > 0)
				free(cfg->map[--i]);
			free(cfg->map);
			cfg->map = NULL;
			return (0);
		}
		i++;
	}
	cfg->map[height] = NULL;
	return (1);
}

int	map_width(char **lines, int start, int height)
{
	int	i;
	int	len;
	int	max_width;

	i = 0;
	max_width = 0;
	while (i < height)
	{
		len = ft_strlen(lines[start + i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

static int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_blank_lines(char **lines, int start)
{
	int	i;
	int	blank;

	i = start;
	blank = 0;
	while (lines[i])
	{
		if (is_blank_line(lines[i]))
			blank = 1;
		else if (blank)
			return (0);
		i++;
	}
	return (1);
}
