/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:58:08 by jcueille          #+#    #+#             */
/*   Updated: 2019/10/31 10:52:44 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*memsrc;
	unsigned char		*memdst;
	unsigned char		c_unsignd;

	memdst = (unsigned char *)dst;
	c_unsignd = (unsigned char)c;
	memsrc = (unsigned char*)src;
	while (n--)
	{
		*memdst = *memsrc++;
		if (*memdst++ == c_unsignd)
			return ((void*)memdst);
	}
	return (NULL);
}
