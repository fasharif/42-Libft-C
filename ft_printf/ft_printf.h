/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:45:04 by fasharif          #+#    #+#             */
/*   Updated: 2022/08/12 16:49:48 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	pf_putchar(char c);
int	pf_putstr(char *str);
int	pf_putnbr(int n);
int	pf_putunsigned(unsigned int n);
int	pf_puthex(unsigned int n, char x);
int	pf_putpointer(unsigned long long p);

#endif
