/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:17:09 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/23 17:11:56 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**get_tex_slot(t_setup *cfg, char *id)
{
	if (!ft_strncmp(id, "NO ", 3))
		return (&cfg->tex_n);
	if (!ft_strncmp(id, "SO ", 3))
		return (&cfg->tex_s);
	if (!ft_strncmp(id, "WE ", 3))
		return (&cfg->tex_w);
	if (!ft_strncmp(id, "EA ", 3))
		return (&cfg->tex_e);
	return (NULL);
}

static t_error	read_path(char *rest, char **path)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	while (rest[start] == ' ')
		start++;
	end = start;
	while (rest[end] && rest[end] != ' ')
	{
		if (rest[end] == '\t')
			return (ERR_TEXTURE);
		end++;
	}
	if (end == start)
		return (ERR_TEXTURE);
	i = end;
	while (rest[i] == ' ')
		i++;
	if (rest[i])
		return (ERR_TEXTURE);
	*path = ft_substr(rest, start, end - start);
	if (!*path)
		return (ERR_MALLOC);
	return (OK);
}

static t_error	check_tex_file(char *path)
{
	int	fd;

	if (check_extension(path, ".xpm"))
		return (ERR_TEXTURE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_TEXTURE);
	close(fd);
	return (OK);
}

t_error	parse_texture(char *rest, char **slot)
{
	char	*path;
	t_error	err;

	if (*slot)
		return (ERR_DUP_ELEMENT);
	err = read_path(rest, &path);
	if (err != OK)
		return (err);
	err = check_tex_file(path);
	if (err != OK)
	{
		free(path);
		return (err);
	}
	*slot = path;
	return (OK);
}
