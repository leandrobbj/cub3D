/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:48:19 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/23 17:11:03 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* returns 0 if path ends with ext (and has something before it) */
int	check_extension(char *path, char *ext)
{
	size_t	path_len;
	size_t	ext_len;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (path_len <= ext_len)
		return (1);
	return (ft_strncmp(path + path_len - ext_len, ext, ext_len + 1) != 0);
}

static char	*read_all(int fd)
{
	char	*line;
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	line = get_next_line(fd);
	while (buffer && line)
	{
		tmp = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		buffer = tmp;
		if (buffer)
			line = get_next_line(fd);
	}
	return (buffer);
}

static int	count_lines(char *s)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			n++;
		i++;
	}
	if (i > 0 && s[i - 1] != '\n')
		n++;
	return (n);
}

static char	**split_lines(char *s)
{
	char	**lines;
	int		n;
	int		i;
	int		len;

	n = count_lines(s);
	lines = malloc(sizeof(char *) * (n + 1));
	if (!lines)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		len = 0;
		while (s[len] && s[len] != '\n')
			len++;
		lines[i] = ft_substr(s, 0, len);
		if (!lines[i])
		{
			free_lines(lines);
			return (NULL);
		}
		s += len + (s[len] == '\n');
	}
	lines[n] = NULL;
	return (lines);
}

/* NULL = malloc error. An empty file gives {NULL} (lines[0] == NULL) */
char	**read_lines(int fd)
{
	char	*all;
	char	**lines;

	all = read_all(fd);
	if (!all)
		return (NULL);
	lines = split_lines(all);
	free(all);
	return (lines);
}
