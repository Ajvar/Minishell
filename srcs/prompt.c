/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:27:21 by jcueille          #+#    #+#             */
/*   Updated: 2021/02/02 16:05:47 by jcueille         ###   ########.fr       */
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

static char *ft_trim_home(char *cwd)
{
    int i;
    char *path;

    i = 6;
    while (cwd[i] != '/')
        i++;
    path = ft_substr(cwd, i, ft_strlen(cwd));
    return (path);
}

void ft_prompt()
{
    char cwd_buffer[4096];
    char *cwd;
    char *path;

    cwd = getcwd(cwd_buffer, 4096);
    if (ft_strncmp(cwd, "/home", 5) == 0)
    {
        path = ft_trim_home(cwd);
        write (1, "~", 1);
    }
    else
        path = ft_strdup(cwd);
    ft_putstr_fd("\e[1;32m", 1);
    ft_putstr_fd(path, 1);
    ft_putstr_fd(" > \e[0m", 1);
    free (path);
}