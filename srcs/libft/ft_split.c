/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:25:50 by jcueille          #+#    #+#             */
/*   Updated: 2019/10/31 10:54:11 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char		*ft_malloc_and_fill(char const *s, char c)
{
	char		*res;
	int			i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(res = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int		ft_countword(char const *s, char c)
{
	int			i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			i++;
			while (*s != c && *s)
				s++;
		}
	}
	return (i);
}

char			**ft_split(char const *s, char c)
{
	char		**res;
	int			i;
	char		words;

	if (!s)
		return (NULL);
	i = 0;
	words = ft_countword(s, c);
	if (!(res = malloc(sizeof(res) * (words + 1))))
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			res[i] = ft_malloc_and_fill(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	res[i] = NULL;
	return (res);
}
