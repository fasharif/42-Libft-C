/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:17:37 by fasharif          #+#    #+#             */
/*   Updated: 2022/08/07 15:47:59 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

static char	*ft_makewrds(char *word, char const *s, int x, int leng_wd)
{
	int		i;

	i = 0;
	while (leng_wd > 0)
		word[i++] = s[x - leng_wd--];
	word[i] = '\0';
	return (word);
}

static char	**ft_wrdsplit(char **result, char const *s, char c, int wordcnt)
{
	int		i;
	int		x;
	int		leng_wd;

	i = 0;
	x = 0;
	leng_wd = 0;
	while (s[x] != '\0' && i < wordcnt)
	{
		while (s[x] != '\0' && s[x] == c)
			x++;
		while (s[x] && s[x] != c)
		{
			x++;
			leng_wd++;
		}
		result[i] = (char *)malloc(sizeof(char) * (leng_wd + 1));
		if (!result[i])
			return (NULL);
		ft_makewrds(result[i], s, x, leng_wd);
		leng_wd = 0;
		i++;
	}
	result[i] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		wordcnt;
	char	**result;

	if (!s)
		return (NULL);
	wordcnt = ft_countword(s, c);
	result = (char **)malloc(sizeof(char *) * (wordcnt + 1));
	if (!result)
		return (NULL);
	ft_wrdsplit(result, s, c, wordcnt);
	return (result);
}
