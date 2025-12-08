/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:48:50 by fasharif          #+#    #+#             */
/*   Updated: 2022/08/07 15:44:33 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*skip_whitespace(const char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return (str);
}

int	ft_atoi(const char	*str)
{
	long	n;
	long	sign;

	n = 0;
	sign = 1;
	str = skip_whitespace(str);
	if (*str == '-')
		sign = -1;
	if ((*str == '-') || (*str == '+'))
		str++;
	while ((*str != '\0') && ('0' <= *str) && (*str <= '9'))
	{
		n = (n * 10) + (*str - '0');
		if (n > 9223372036854775807 && sign == 1)
			return (-1);
		if (n > 9223372036854775807 && sign == -1)
			return (0);
		str++;
	}
	return (n * sign);
}
