/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42liboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:36:30 by lbraga            #+#    #+#             */
/*   Updated: 2025/10/23 18:44:03 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

/* int main(void)
{
	char	*buffer = "abcde";

	printf("%p\n", buffer);
	printf("%p\n", ft_strchr(buffer, 'A'));
	printf("%p\n", ft_strchr(buffer, 'c'));
	printf("%p\n", ft_strchr(buffer, '\0'));
	return (0);
} */
