/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:58:21 by jcueille          #+#    #+#             */
/*   Updated: 2021/03/23 22:00:24 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	res;

	res = 0;
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (res != 0)
			return (res);
		i++;
	}
	return (0);
}