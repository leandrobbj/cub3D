/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:11:56 by lbraga            #+#    #+#             */
/*   Updated: 2025/12/05 19:09:06 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_null(char **s1)
{
	free(*s1);
	*s1 = NULL;
}

// Concatenates string s1 & s2 = s1, freeing older s1
void	ft_strjoinfree1(char **s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!*s1)
		return ;
	if (!s2)
		return (free_null(s1));
	i = ft_strlen(*s1);
	j = ft_strlen(s2);
	str = (char *)malloc((i + j + 1) * sizeof(char));
	if (!str)
		return (free_null(s1));
	ft_strlcpy(str, *s1, i + 1);
	ft_strlcat(str, s2, i + j + 1);
	free(*s1);
	*s1 = str;
}
