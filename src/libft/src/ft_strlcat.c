/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42liboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:46:35 by lbraga            #+#    #+#             */
/*   Updated: 2025/10/23 18:44:06 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	dlen;

	i = 0;
	dlen = ft_strlen(dst);
	if (dsize <= dlen)
		return (dsize + ft_strlen(src));
	while (src[i] && dsize > dlen + i + 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + ft_strlen(src));
}

/* #include <stdio.h>

int	main(void)
{
	char s1[23] = "where is my ";
 	char *s2 = "malloc ???";
 	char *s3 = "where is my malloc ???";
	size_t result = ft_strlcat(s1, s2, 22 + 1);

	printf("%s\n", s1);
	printf("%lu\n", result);
	return (0);	
} */
