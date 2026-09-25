/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:45:11 by fasharif          #+#    #+#             */
/*   Updated: 2022/08/12 17:45:39 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** The va_list is passed by pointer. Passing it by value and calling va_arg in
** the callee leaves the caller's copy indeterminate, which breaks on ARM64.
*/
static int	print_specifier(char c, va_list *args)
{
	unsigned long long	p;

	if (c == 'c')
		return (pf_putchar((char)va_arg(*args, int)));
	else if (c == 's')
		return (pf_putstr(va_arg(*args, char *)));
	else if (c == 'x' || c == 'X')
		return (pf_puthex(va_arg(*args, unsigned int), c));
	else if (c == '%')
		return (pf_putchar('%'));
	else if (c == 'd' || c == 'i')
		return (pf_putnbr(va_arg(*args, int)));
	else if (c == 'u')
		return (pf_putunsigned(va_arg(*args, unsigned int)));
	else if (c == 'p')
	{
		p = (unsigned long long)(uintptr_t)va_arg(*args, void *);
		if (p == 0)
			return (pf_putstr("0x0"));
		return (pf_putstr("0x") + pf_putpointer(p));
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		sum;

	if (!str)
		return (0);
	va_start(args, str);
	i = 0;
	sum = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (!str[i])
				break ;
			sum += print_specifier(str[i], &args);
		}
		else
			sum += pf_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (sum);
}
