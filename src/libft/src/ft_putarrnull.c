/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:11:56 by lbraga            #+#    #+#             */
/*   Updated: 2025/11/24 20:09:54 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putarrnull(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		ft_putstrnul(array[i++]);
	write(1, "(null)\n", 7);
}
