/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:27:15 by jcueille          #+#    #+#             */
/*   Updated: 2021/02/02 17:02:28 by jcueille         ###   ########.fr       */
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

char          **g_env;
char          **g_path;
extern char   ** environ;

int ft_process(char **commands)
{
  int i;

  i = 0;
  while (commands[i])
  {

    i++;
  }
  return (0);
}

void ft_free_array(char **array)
{
  int i;

  i = 0;
  while (array[i])
  {
    free(array[i]);
    i++;
  }
  free(array);
  array = NULL;
}

char **ft_arr_cpy(char **src)
{
  int   i;
  char  **dest;

  i = 0;
  while (src[i])
    i++;
  printf("Before malloc: %d\n", i);
  dest = malloc(sizeof(char *) * (i + 1));
  printf("After malloc: %d\n", i);
  dest[i] = NULL;
  i--;
  while (i >= 0)
  {
    dest[i] = ft_strdup(src[i]);
    i--;
  }
  printf("End of function: %d\n", i);
  return (dest);
}

void  ft_set_path(void)
{
  int i;

  i = 0;
  if (g_path)
    ft_free_array(g_path);
  while (g_env[i])
  {
    if  ( ! ft_strncmp(g_env[i], "PATH=", 5))
    {
      g_path = ft_split(&g_env[i][5], ':');
      break;
    }
    i++;
  }
}

int main()
{
  char  *buffer;
  char  **commands;
  int   n;
  
  g_env = ft_arr_cpy(environ);
  g_path = NULL;
  ft_set_path();
  //int i = 0;
  //while (g_path[i])
  //{
  //  printf("%s\n", g_path[i]);
  //  i++;
  //}
  while (1)
  {
    ft_prompt();
    n = get_next_line(0, &buffer);
    commands = ft_split(buffer, ';');
    free(buffer); 
    ft_process(commands);
  }
  ft_free_array(g_env);
  ft_free_array(g_path);
  return 0;
}

  //ft_free_array(splited_args);


  //while (true)
  //{
  //  printf("enter value");
  //  child_pid = fork();
//
//
//
    //  n = scanf("%m[a-z]", &strin);
    //  printf("%s", strin);
//
    //  free(strin);
    //}
    //// The child process
    //if (child_pid == 0) {
    //    printf("### Child ###\nCurrent PID: %d and Child PID: %d\n",
    //           getpid(), child_pid);
    //    sleep(1); // Sleep for one second
    //} else {
    //    wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
    //    printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
    //           getpid(), child_pid);
    //}