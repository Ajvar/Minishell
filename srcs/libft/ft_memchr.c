/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:01:51 by jcueille          #+#    #+#             */
/*   Updated: 2019/10/31 10:48:54 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ss;
	unsigned char c_unsignd;

	ss = (unsigned char *)s;
	c_unsignd = (unsigned char)c;
	while (n--)
	{
		if (c_unsignd == *ss)
			return (ss);
		ss++;
	}
	return (NULL);
}
