/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:47:30 by fasharif          #+#    #+#             */
/*   Updated: 2022/08/12 16:49:44 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_hex_digits(unsigned long long nb)
{
	int	i;

	i = 1;
	while (nb >= 16)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

static void	put_base16(unsigned long long nb, char *base)
{
	if (nb >= 16)
		put_base16(nb / 16, base);
	pf_putchar(base[nb % 16]);
}

int	pf_puthex(unsigned int n, char x)
{
	char	*base;

	base = "0123456789abcdef";
	if (x == 'X')
		base = "0123456789ABCDEF";
	put_base16(n, base);
	return (count_hex_digits(n));
}

int	pf_putpointer(unsigned long long p)
{
	put_base16(p, "0123456789abcdef");
	return (count_hex_digits(p));
}
