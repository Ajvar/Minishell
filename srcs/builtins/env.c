/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:57:43 by jcueille          #+#    #+#             */
/*   Updated: 2021/03/19 15:49:47 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../Minishell.h"
#include <unistd.h>

void	ft_env(void)
{
	t_env		*env;

	env = g_env;
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		write(1, "=", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}
