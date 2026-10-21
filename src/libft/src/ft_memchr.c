/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42liboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:41:25 by lbraga            #+#    #+#             */
/*   Updated: 2025/10/23 18:43:53 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chr;

	str = (unsigned char *)s;
	chr = (unsigned char)c;
	if (n == 0)
		return (NULL);
	while (*str != chr && --n)
		str++;
	if (*str == chr)
		return (str);
	return (NULL);
}

/* int	main(void)
{
	char	*str = "abcde";
	printf("%p\n", str);
	printf("%p\n", ft_memchr(str, 'x', 5));
	printf("%p\n", ft_memchr(str, '\0', 6));
	printf("%c\n", str[6]);
	printf("%p\n", ft_memchr(str, '%', 7));
	return (0);
} */
