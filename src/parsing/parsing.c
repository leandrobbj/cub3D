/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:37:37 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/21 17:39:18 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_error	parse_lines(char **lines, t_setup *cfg)
{
	t_error	err;
	int		start;

	err = parse_elements(lines, &start, cfg);
	if (err != OK)
		return (err);
	return (check_map(lines, start, cfg));
}

t_error	parse_file(char *path, t_setup *cfg)
{
	int		fd;
	char	**lines;
	t_error	err;

	init_config(cfg);
	if (check_extension(path, ".cub"))
		return (ERR_EXT);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_OPEN);
	lines = read_lines(fd);
	close(fd);
	if (!lines)
		return (ERR_READ);
	if (!lines[0])
	{
		free_lines(lines);
		return (ERR_EMPTY);
	}
	err = parse_lines(lines, cfg);
	free_lines(lines);
	if (err != OK)
		free_config(cfg);
	return (err);
}
