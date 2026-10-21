/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42liboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:40:07 by lbraga            #+#    #+#             */
/*   Updated: 2025/10/23 18:44:13 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && isset(s1[i], set))
		i++;
	while (j > i && isset(s1[j - 1], set))
		j--;
	return (ft_substr(s1, i, j - i));
}

static int	isset(char c, const char *set)
{
	while (*set && c != *set)
		set++;
	if (c == *set)
		return (1);
	else
		return (0);
}

/* int	main(void)
{
	char	*s1 = "dedededdeDebora de Jesusdeddedde";
	char	*set = "de";
	printf("%s\n", ft_strtrim(s1, set));
	return (0);
} */
