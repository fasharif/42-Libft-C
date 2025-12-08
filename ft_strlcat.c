/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:53:51 by fasharif          #+#    #+#             */
/*   Updated: 2022/07/28 16:29:08 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (((char *)dest)[i] && i < dstsize)
		i++;
	j = i;
	while (((char *)src)[i - j] && i + 1 < dstsize)
	{
		((char *)dest)[i] = ((char *)src)[i - j];
		i++;
	}
	if (j < dstsize)
		((char *)dest)[i] = '\0';
	return (j + ft_strlen(((char *)src)));
}
