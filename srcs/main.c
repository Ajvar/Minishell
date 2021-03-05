/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:27:15 by jcueille          #+#    #+#             */
/*   Updated: 2021/02/12 14:30:21 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <strings.h>
#include "libft/libft.h"
#include "Minishell.h"

int				ft_parse(char *s)
{
	
}

int				ft_process(int n, char **pipes)
{
	int			fd[2];
	int			i;
	pid_t		child;
	char		**args;

	i = 0;
	pipe(fd);

}

/*
**	splits the commands at pipes
**	and send the result to a function that will process the result
**	(parse it and execute it)
*/

int				ft_get_pipes(char **commands)
{
	int			i;
	int			pipes_nbr;
	char		**pipes;

	i = -1;
	pipes_nbr = 0;
	while (commands[++i])
	{
		pipes = ft_split(commands[i], '|');
		while (pipes[pipes_nbr])
			pipes_nbr++;
		if (ft_process(pipes_nbr, pipes) == -1)
		{
			ft_free_array(pipes);
			return (-1);
		}
		ft_free_array(pipes);
	}
	return (0);
}

void			ft_free_array(char **array)
{
	int			i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

char			**ft_arr_cpy(char **src)
{
	int			i;
	char		**dest;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	dest[i] = NULL;
	i--;
	while (i >= 0)
	{
		dest[i] = ft_strdup(src[i]);
		i--;
	}
	return (dest);
}

// char			**ft_path(void)
// {
// 	int			i;
// 	char		*path;

// 	i = 0;
// 	while (g_env[i])
// 	{
// 		if (!(ft_strncmp(g_env[i], "PATH=", 5)))
// 		{
// 			path = ft_split(&g_env[i][5], ':');
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (path);
// }

void ft_env(void)
{
	extern char	**environ;
	t_list		*env;
	int i;

	i = -1;
	while (environ[++i])
	{
		env = ft_lstnew(environ[i]);
		ft_lstadd_back(&g_env, env);
	}
	printf("DONE...\n");
	env = g_env;
	while (env)
	{	
		//ft_putstr_fd(env->content, 1);
		//ft_putstr_fd("\n", 1);
		printf("%s\n", env->content);
		env = env->next;
	}
}

int				main(void)
{
	char		**commands;
	char		*buffer;
	int			n;

	while (1)
	{
		g_env = ft_lstnew(NULL);
		ft_env();
		ft_prompt();
		n = get_next_line(0, &buffer);
		commands = ft_split(buffer, ';');
		free(buffer);
		ft_get_pipes(commands);
	}
	ft_free_array(g_env);
	return (0);
}
