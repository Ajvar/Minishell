/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:08:25 by jcueille          #+#    #+#             */
/*   Updated: 2021/03/22 15:25:20 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *res;

	res = NULL;
	if ((res = malloc(sizeof(t_list))))
	{
		res->content = content;
		res->next = NULL;
	}
	return (res);
}
