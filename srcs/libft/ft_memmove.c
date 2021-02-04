/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:34:13 by jcueille          #+#    #+#             */
/*   Updated: 2019/10/30 15:32:07 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char		*ssrc;
	unsigned char			*ddst;
	size_t					i;

	i = len;
	ddst = (unsigned char *)dst;
	ssrc = (unsigned char *)src;
	if (ssrc < ddst)
		while (i--)
			ddst[i] = ssrc[i];
	if (ssrc > ddst)
		ft_memcpy(dst, src, len);
	return (dst);
}
