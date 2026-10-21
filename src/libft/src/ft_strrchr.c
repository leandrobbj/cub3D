/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42liboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:50:51 by lbraga            #+#    #+#             */
/*   Updated: 2025/10/23 18:44:12 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0 && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

/* int main(void)
{
	char	*buffer = "abcde";

	printf("%p\n", buffer);
	printf("%p\n", ft_strrchr(buffer, 'A'));
	printf("%p\n", ft_strrchr(buffer, 'c'));
	printf("%p\n", ft_strrchr(buffer, '\0'));
	return (0);
} */
