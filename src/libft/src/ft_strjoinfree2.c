/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:11:56 by lbraga            #+#    #+#             */
/*   Updated: 2025/12/05 19:12:21 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_null(char **s1, char **s2)
{
	free(*s1);
	free(*s2);
	*s1 = NULL;
}

// Concatenates string s1 & s2 = s1, freeing older s1 & s2
void	ft_strjoinfree2(char **s1, char **s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!*s1 || !*s2)
		return (free_null(s1, s2));
	i = ft_strlen(*s1);
	j = ft_strlen(*s2);
	str = (char *)malloc((i + j + 1) * sizeof(char));
	if (!str)
		return (free_null(s1, s2));
	ft_strlcpy(str, *s1, i + 1);
	ft_strlcat(str, *s2, i + j + 1);
	free(*s1);
	free(*s2);
	*s1 = str;
}
