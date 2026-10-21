/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:07:55 by lbraga            #+#    #+#             */
/*   Updated: 2025/12/07 13:18:39 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (*buffer)
		ft_strjoinfree1(&line, buffer);
	if (!line)
		return (NULL);
	find_line(fd, &line, buffer);
	if (!line)
		return (NULL);
	clean_line(line, buffer);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

void	find_line(int fd, char **line, char *buffer)
{
	ssize_t		bytes;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(*line);
			*line = NULL;
			buffer[0] = '\0';
			return ;
		}
		buffer[bytes] = '\0';
		ft_strjoinfree1(line, buffer);
	}
}

void	clean_line(char *line, char *buffer)
{
	size_t	i;
	char	*needle;

	i = 0;
	needle = ft_strchr(line, '\n');
	if (needle)
		needle[1] = '\0';
	needle = ft_strchr(buffer, '\n');
	if (!needle)
		buffer[0] = '\0';
	else
	{
		needle++;
		while (needle[i])
		{
			buffer[i] = needle[i];
			i++;
		}
		buffer[i] = '\0';
	}
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("nls.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/
