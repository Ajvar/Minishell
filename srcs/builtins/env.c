/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:57:43 by jcueille          #+#    #+#             */
/*   Updated: 2021/02/12 14:33:13 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../Minishell.h"

ft_env()
{
	t_list		*env;

	env = g_env;
	while (env)
	{	
		ft_putstr_fd(env->content, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}