/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_intoverflow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:12:06 by lbraga            #+#    #+#             */
/*   Updated: 2025/11/03 20:51:33 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol_intoverflow(const char *nptr)
{
	long	s;
	long	r;

	s = 1;
	r = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*(nptr++) == '-')
			s = -s;
	while (ft_isdigit(*nptr))
	{
		r = (r * 10) + (*(nptr++) - '0');
		if (r * s > INT_MAX || r * s < INT_MIN)
			return (LONG_MAX);
	}
	return (r * s);
}
