/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:50:04 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/21 17:55:03 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_setup *cfg)
{
	cfg->color_c = -1;
	cfg->color_f = -1;
/* 	cfg->map = NULL;
	cfg->dir = 0;
	cfg->pos_x = 0;
	cfg->pos_y = 0;
	cfg->tex_n = NULL;
	cfg->tex_s = NULL;
	cfg->tex_e = NULL;
	cfg->tex_w = NULL; */
}

void	free_config(t_setup *cfg)
{
	free(cfg->tex_n);
	free(cfg->tex_s);
	free(cfg->tex_e);
	free(cfg->tex_w);
	free_lines(cfg->map);
}

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}
