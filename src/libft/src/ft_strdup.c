/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42liboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:23:31 by lbraga            #+#    #+#             */
/*   Updated: 2025/10/23 18:44:04 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	dsize;

	dsize = ft_strlen(s) + 1;
	str = (char *)malloc(dsize * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, dsize);
	return (str);
}

/* int	main(void)
{
	char	*s = "Meu deus";
	char	*d = ft_strdup(s);
	printf("%s\n", d);
	free(d);
	printf("%s\n", d);
	return (0);
} */
