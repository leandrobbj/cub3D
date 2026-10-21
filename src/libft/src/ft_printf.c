/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:57:43 by lbraga            #+#    #+#             */
/*   Updated: 2025/12/01 22:25:01 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sort(va_list args, char format);

int	ft_printf(const char *format, ...)
{
	int		cnt;
	va_list	args;

	if (!format)
		return (-1);
	cnt = 0;
	va_start(args, format);
	while (*format)
	{
		while (*format != '%' && *format)
			cnt += write (1, format++, 1);
		if (*format == '%' && *++format)
			cnt += ft_sort(args, *format++);
	}
	va_end(args);
	return (cnt);
}

static int	ft_sort(va_list args, char format)
{
	if (format == 'c')
		return (f_chr(va_arg(args, int)));
	else if (format == 's')
		return (f_str(va_arg(args, char *)));
	else if (format == 'p')
		return (f_ptr(va_arg(args, void *)));
	else if (format == 'i' || format == 'd')
		return (f_int(va_arg(args, int)));
	else if (format == 'u' || format == 'x' || format == 'X')
		return (f_uint(va_arg(args, unsigned int), format));
	else
		return (write(1, &format, 1));
}
