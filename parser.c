/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:12:48 by jcueille          #+#    #+#             */
/*   Updated: 2021/03/08 19:56:03 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "./srcs/libft/libft.h"

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env *g_env;

void	ft_new_env(void)
{
	t_env *tmp;

	g_env = malloc(sizeof(t_env));
	g_env->key = ft_strdup("VAR");
	g_env->value = ft_strdup("VALUE");
	tmp = malloc(sizeof(t_env));
	g_env->next = tmp;
	tmp->key = ft_strdup("VARZ");
	tmp->value = ft_strdup("VALUZ");
}

/*
**	REMOVE A SINGLE CHAR FROM A STRING
*/

static void	ft_remove_char(char *s, int i)
{
	char	*res;
	int		j;

	if (!(res = malloc(ft_strlen(s) * sizeof(char))))
		return ;
	j = -1;
	while (++j < i)
		res[j] = s[j];
	i = j;
	while (s[++j])
	{
		res[i] = s[j];
		i++;
	}
	res[j - 1] = '\0';
	free(s);
	s = ft_strdup(res);
	free(res);
}

/*
**	CHECKS IF VAR BRACKETS ARE CLOSED
*/

static int	ft_bracket_check(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == '}')
			return (1);
		i++;
	}
	printf("ERROR: BRACKET MISSING\n");
	return (0);
}

static void	ft_error(void)
{
	printf("error\n");
	exit(1);
}

static void	ft_expand(char *s, int i)
{
	char	*res;

	res = NULL;
	if (s[i + 1] == '{' || ft_isalpha(s[i + 1]))
	{
		ft_remove_char(s, i);
		if (s[i] == '{')
		{
			if (!(ft_bracket_check(s, i)))
				ft_error();
		}
	}
}

/*
**	STRING SANS QUOTES
*/

static char	*ft_string(char *s, int *i)
{
	int		j;
	char	*res;

	j = *i;
	while (s[j] && s[j] != ' ' && s[j] != '\"' && s[j] != '\'' && s[j] != '$')
	{
		if (s[j] == '\\')
		{
			ft_remove_char(s, j);
			j++;
		}
		j++;
	}
	res = ft_substr(s, *i, j - *i);
	(*i) = j - 1;
	return (res);
}

static char	*ft_single(char *s, int *i)
{
	int		j;
	char	*res;

	j = (*i) + 1;
	while (s[j] && s[j] != '\'')
	{
		if (s[j] == '\\')
			ft_remove_char(s, j);
		j++;
	}
	res = ft_substr(s, (*i) + 1, j - (*i + 1));
	(*i) = j;
	return (res);
}

/*
**	RETRIEVE VAR VALUE
*/

static char	*ft_search_var(char *s, int *inc, int flag, int *i)
{
	int		k;
	int		j;
	t_env	*tmp;
	char	*name;
	char	*res;

	k = *i + 1;
	(*inc) = 0;
	tmp = g_env;
	res = NULL;
	if (!(s[k]))
		return (res);
	if (s[k] == '{')
	{
		if (!(ft_bracket_check(s, k)))
			return (res);
		(*inc) += 2;
		k++;
	}
	j = k;
	while (s[j] && s[j] != ' ' && s[j] != '}')
		j++;
	name = ft_substr(s, k, j - k);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, name, ft_strlen(tmp->key)) == 0)
			res = ft_strdup(tmp->value);
		/*int l = ft_strncmp(tmp->key, name, ft_strlen(tmp->key));
		**	if (l == 0)
		**	res = ft_strdup(tmp->value);
		*/
		tmp = tmp->next;
	}
	*inc += ft_strlen(name);
	free(name);
	if (s[++j] && flag == 1)
		name = ft_strjoin(res, &s[j]);
	else
		return (res);
	free(res);
	return (name);
}

/*
**	DOLLAR DANS QUOTES
*/

static char	*ft_dollar(char *s, int *i, int *j)
{
	char	*tmp;
	char	*tmp2;
	char	*res;
	int		inc;

	res = ft_search_var(s, &inc, 1, j);
	*j = inc - 1;
	free(s);
	return (res);
}

/*
**	DOUBLE QUOTES
*/

static char	*ft_double(char *s, int *i)
{
	int		j;
	char	*s_copy;
	char	*res;

	j = *i + 1;
	if (!(s[j]))
		return (NULL);
	s_copy = ft_strdup(&s[j]);
	j = 0;
	while (s_copy[j] && s_copy[j] != '\"')
	{
		if (s_copy[j] == '\\')
		{
			if (s_copy[j + 1] == '\\' || s_copy[j + 1] == '\"')
			{
				ft_remove_char(s_copy, j);
				j++;
			}
		}
		if (s[j] == '$')
			s_copy = ft_dollar(s_copy, i, &j);
		j++;
	}
	if (s_copy[j] == '\0')
		printf("ERROR: DOUBLE QUOTE NOT CLSOED\n");
	s_copy[j] = '\0';
	(*i) += j + 1;
	return (s_copy);
}

/*
**	APPLY FT ACCORDING TO QUOTES OR NOT
*/

char		*ft_apply(char *s, int *i, char *(*f)(char *s, int *i), char *res)
{
	char	*tmp;
	char	*tmp_bis;

	tmp = (*f)(s, i);
	if (!(res))
		tmp_bis = ft_strdup(tmp);
	else
		tmp_bis = ft_strjoin(res, tmp);
	free(res);
	res = NULL;
	free(tmp);
	return (tmp_bis);
}


//ADDS STR TO COMMANDS LIST WHEN SPLITTING SPACE IS REACHED

void		ft_empty_buffer(char *s, t_list **command)
{
	t_list	*tmp;
	char	*copy;

	if (!(s))
		return ;
	copy = ft_strdup(s);
	tmp = ft_lstnew(copy);
	ft_lstadd_back(command, tmp);
}

t_list		*ft_parse(char *s)
{
	t_list	*command;
	char	*res;
	int		i;
	int		inc;

	i = -1;
	res = NULL;
	command = NULL;
	while (s[++i])
	{
		if (s[i] == '\"')
		{
			res = ft_apply(s, &i, &ft_double, res);
			continue;
		}
		else if (s[i] == ' ')
		{
			ft_empty_buffer(res, &command);
			free(res);
			res = NULL;
			continue ;
		}
		if (s[i] == '\'')
		{
			res = ft_apply(s, &i, &ft_single, res);
			continue;
		}
		else if (s[i] == '$')
		{
			res = ft_search_var(s, &inc, 0, &i);
			i += inc;
		}
		else
			res = ft_apply(s, &i, &ft_string, res);
	}
	if (res)
		ft_empty_buffer(res, &command);
	while (command)
	{
		printf("S IS %s\n", command->content);
		command = command->next;
	}
}

int	main(void)
{
	int n = 0;
	int k = 5;
	int *j = &k;
	int *i = &n;
	char *s;

	ft_new_env();
/*	
**	s = ft_strdup("\"${VAR}\" \"\'lol\'\" ${VR} mdr");
*/
	s = ft_strdup("\'\"lol&\"\'  \"\'lol\'\" $VAR ${VAR} $WRONG \"$VAR\", \'$VAR\' \\");
	ft_parse(s);
	printf("%s\n", s);
	return (0);
}
