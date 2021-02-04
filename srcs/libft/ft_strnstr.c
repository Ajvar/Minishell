/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:32:20 by jcueille          #+#    #+#             */
/*   Updated: 2019/10/31 10:48:45 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && len && len > i)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] && (j + i) < len)
			j++;
		if (needle[j] == '\0')
			return ((char*)haystack + (i));
		i++;
	}
	return (NULL);
}
