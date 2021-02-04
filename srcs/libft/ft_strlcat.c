/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:08:21 by jcueille          #+#    #+#             */
/*   Updated: 2019/10/31 10:54:22 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t res;

	i = 0;
	j = 0;
	res = 0;
	while (dst[res] && (res < dstsize))
		res++;
	while (src[i])
	{
		if (dstsize > 0)
			if (res + i < dstsize - 1)
				dst[res + (j++)] = src[i];
		i++;
	}
	if (dstsize > 0 && res < dstsize)
		dst[res + j] = '\0';
	return (res + i);
}
