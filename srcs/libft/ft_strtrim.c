/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:34:11 by jcueille          #+#    #+#             */
/*   Updated: 2021/02/01 17:41:47 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *set, char const *s1)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (set[i] && s1[k])
	{
		if (set[i] == (char)s1[k])
		{
			k++;
			i = 0;
			continue ;
		}
		i++;
	}
	return (k);
}

static int	ft_end(char const *set, char const *s1)
{
	int		j;
	int		i;

	j = 0;
	while (s1[j])
		j++;
	j--;
	i = 0;
	while (set[i])
	{
		if (set[i] == (char)s1[j])
		{
			j--;
			i = 0;
			continue ;
		}
		i++;
	}
	return (j);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		k;
	int		j;
	char	*res;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	j = 0;
	k = ft_start(set, s1);
	if (!(s1[k]))
		return (ft_memcpy(res = malloc(1), "\0", 1));
	j = ft_end(set, s1);
	res = ft_substr(s1, k, j - k + 1);
	return (res);
}
