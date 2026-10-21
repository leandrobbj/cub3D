/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:50:11 by lbraga            #+#    #+#             */
/*   Updated: 2025/11/24 22:03:26 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cntwrd(char const *s, char c);
static int	cpywrds(char const *s, char **words, char c);

char	**ft_split(char const *s, char c)
{
	int		w;
	int		count;
	char	**words;

	if (!s)
		return (NULL);
	count = cntwrd(s, c);
	words = (char **)malloc((count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	w = cpywrds(s, words, c);
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

static int	cntwrd(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static int	cpywrds(char const *s, char **words, char c)
{
	int		w;
	size_t	end;
	size_t	sta;

	w = 0;
	end = 0;
	while (s[end])
	{
		while (s[end] == c)
			end++;
		sta = end;
		while (s[end] != c && s[end])
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
