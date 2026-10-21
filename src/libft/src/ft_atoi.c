/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:12:06 by lbraga            #+#    #+#             */
/*   Updated: 2025/10/24 17:48:19 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	s;
	int	r;

	s = 1;
	r = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*(nptr++) == '-')
			s = -s;
	}
	while (ft_isdigit(*nptr))
		r = (r * 10) + (*(nptr++) - '0');
	return (r * s);
}

/* int	main(int ac, char **av)
{
	if (ac == 2)
		printf("%d", ft_atoi(av[1]));
	printf("\n");
	return (0);
} */
