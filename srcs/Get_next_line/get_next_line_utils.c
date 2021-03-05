/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:59:53 by jcueille          #+#    #+#             */
/*   Updated: 2021/02/16 17:20:04 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		*ft_calloc(size_t count, size_t size)
{
	int		i;
	void	*res;

	i = 0;
	if (!(res = malloc(count * size)))
		return (NULL);
	while (i < (int)count * (int)size)
	{
		*(char*)(res + i) = '\0';
		i++;
	}
	return (res);
}

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (!(res = (char *)ft_calloc(len + 1, sizeof(*res))))
		return (NULL);
	if (start < s_len)
		while (i < len && s[start])
			res[i++] = s[start++];
	return (res);
}

char		*ft_strjoin(char  *s1, char  *s2)

{
	int		i;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	if (!(res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = 0;
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		res[i] = *s2;
		s2++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
