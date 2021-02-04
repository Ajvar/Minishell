/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:33:47 by jcueille          #+#    #+#             */
/*   Updated: 2019/10/30 15:26:16 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*memsrc;
	unsigned char		*memdst;

	if (!dst && !src && n > 0)
		return (NULL);
	memdst = (unsigned char *)dst;
	memsrc = (unsigned char *)src;
	while (n--)
		*memdst++ = *memsrc++;
	return (dst);
}
