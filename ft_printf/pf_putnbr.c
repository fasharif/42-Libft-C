/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:23:40 by fasharif          #+#    #+#             */
/*   Updated: 2022/08/14 15:17:51 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(long nb)
{
	int	i;

	i = 1;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void	put_digits(long nb)
{
	if (nb > 9)
		put_digits(nb / 10);
	pf_putchar(nb % 10 + '0');
}

int	pf_putnbr(int n)
{
	long	nb;
	int		size;

	size = 0;
	nb = n;
	if (nb < 0)
	{
		pf_putchar('-');
		nb = -nb;
		size = 1;
	}
	put_digits(nb);
	return (size + count_digits(nb));
}

int	pf_putunsigned(unsigned int n)
{
	put_digits(n);
	return (count_digits(n));
}
