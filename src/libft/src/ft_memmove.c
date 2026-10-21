/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42liboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:26:19 by lbraga            #+#    #+#             */
/*   Updated: 2025/10/23 18:43:56 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == src)
		return (dest);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (d < s)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}

/* int main(void)
{
	char	buffer[] = "012345ABCD";
	ft_memmove(&buffer[1], &buffer[6], 2);
	printf("%s\n", buffer);
} */
