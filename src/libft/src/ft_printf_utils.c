/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:30:18 by lbraga            #+#    #+#             */
/*   Updated: 2025/12/01 22:25:08 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	f_chr(int c)
{
	return (write(1, &c, 1));
}

int	f_str(char *str)
{
	int	cnt;

	if (!str)
		return (write(1, "(null)", 6));
	cnt = 0;
	while (*str)
		cnt += write(1, str++, 1);
	return (cnt);
}

int	f_ptr(void *ptr)
{
	if (!ptr)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	return (f_uint((size_t)ptr, 'p') + 2);
}

int	f_int(int n)
{
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
		return (f_uint(n, 'u') + 1);
	}
	return (f_uint(n, 'u'));
}

int	f_uint(size_t n, char c)
{
	int		cnt;
	size_t	bs;

	if (c == 'u')
		bs = 10;
	else
		bs = 16;
	cnt = 0;
	if (n >= bs)
		cnt += f_uint(n / bs, c);
	if (c == 'X')
		cnt += write(1, &"0123456789ABCDEF"[n % bs], 1);
	else
		cnt += write(1, &"0123456789abcdef"[n % bs], 1);
	return (cnt);
}
