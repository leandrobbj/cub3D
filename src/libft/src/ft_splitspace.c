/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:40:00 by lbraga            #+#    #+#             */
/*   Updated: 2025/11/26 09:44:02 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cntwrd(char const *s);
static int	cpywrds(char const *s, char **words);

char	**ft_splitspace(char const *s)
{
	int		w;
	int		count;
	char	**words;

	if (!s)
		return (NULL);
	count = cntwrd(s);
	words = (char **)malloc((count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	w = cpywrds(s, words);
	if (w != -1)
	{
		while (w--)
			free(words[w]);
		free(words);
		return (NULL);
	}
	words[count] = NULL;
	return (words);
}

static int	cntwrd(char const *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
			count++;
		while (!ft_isspace(*s) && *s)
			s++;
	}
	return (count);
}

static int	cpywrds(char const *s, char **words)
{
	int		w;
	size_t	end;
	size_t	sta;

	w = 0;
	end = 0;
	while (s[end])
	{
		while (ft_isspace(s[end]))
			end++;
		sta = end;
		while (!ft_isspace(s[end]) && s[end])
			end++;
		if (end > sta)
		{
			words[w] = ft_substr(s, sta, end - sta);
			if (!words[w])
				return (w);
			w++;
		}
	}
	return (-1);
}

//return (-1) means success 
