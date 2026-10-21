/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 18:35:36 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/21 17:52:07 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == '1')
		return (1);
	if (c == '0')
		return (1);
	if (c == ' ')
		return (1);
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'E')
		return (1);
	if (c == 'W')
		return (1);
	return (0);
}

int	check_map_chars(char **lines, int start, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (lines[start + i][j])
		{
			if (!is_valid_map_char(lines[start + i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	set_player_cfg(char c, int j, int i, t_setup *cfg)
{
	cfg->dir = c;
	cfg->pos_x = j;
	cfg->pos_y = i;
}

int	find_player(char **lines, int start, int height, t_setup *cfg)
{
	int		i;
	int		j;
	int		count;
	char	c;

	i = -1;
	count = 0;
	cfg->dir = 0;
	while (++i < height)
	{
		j = -1;
		while (lines[start + i][++j])
		{
			c = lines[start + i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				count++;
				if (count == 1)
					set_player_cfg(c, j, i, cfg);
			}
		}
	}
	return (count);
}
