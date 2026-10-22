/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 15:12:58 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/22 14:53:04 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error	check_map(char **lines, int start, t_setup *cfg)
{
	int	height;
	int	players;

	if (!lines || !lines[start])
		return (ERR_NO_MAP);
	if (!check_blank_lines(lines, start))
		return (ERR_MAP_NOT_LAST);
	height = 0;
	while (lines[start + height])
		height++;
	if (!check_map_chars(lines, start, height))
		return (ERR_MAP_CHAR);
	players = find_player(lines, start, height, cfg);
	if (players == 0)
		return (ERR_MULTIPLE_OR_NO_PLAYER);
	if (players > 1)
		return (ERR_MULTIPLE_OR_NO_PLAYER);
	if (!build_map(lines, start, height, cfg))
		return (ERR_READ);
	if (!check_map_closed(cfg->map, map_width(lines, start, height),
			height))
		return (ERR_MAP_OPEN);
	return (OK);
}
