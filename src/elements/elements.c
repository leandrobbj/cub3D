/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:17:12 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/22 15:42:02 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (line[i] == '\0');
}

static int	elements_complete(t_setup *cfg)
{
	return (cfg->tex_n && cfg->tex_s && cfg->tex_e && cfg->tex_w
		&& cfg->color_c != -1 && cfg->color_f != -1);
}

static int	starts_element(char *line, t_setup *cfg)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (get_tex_slot(cfg, line + i))
		return (1);
	return ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ');
}

static t_error	parse_element_line(char *line, t_setup *cfg)
{
	char	**slot;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	slot = get_tex_slot(cfg, line + i);
	if (slot)
		return (parse_texture(line + i + 2, slot));
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (parse_color(line + i, cfg));
	if (line[i] == '0' || line[i] == '1')
		return (ERR_MISSING_ELEMENT);
	return (ERR_ELEMENT);
}

t_error	parse_elements(char **lines, int *start, t_setup *cfg)
{
	t_error	err;
	int		i;

	i = 0;
	while (lines[i] && !elements_complete(cfg))
	{
		if (!is_empty_line(lines[i]))
		{
			err = parse_element_line(lines[i], cfg);
			if (err != OK)
				return (err);
		}
		i++;
	}
	if (!elements_complete(cfg))
		return (ERR_MISSING_ELEMENT);
	while (lines[i] && is_empty_line(lines[i]))
		i++;
	if (lines[i] && starts_element(lines[i], cfg))
		return (ERR_DUP_ELEMENT);
	*start = i;
	return (OK);
}
