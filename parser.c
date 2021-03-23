/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:12:48 by jcueille          #+#    #+#             */
/*   Updated: 2021/03/23 15:22:50 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "./srcs/libft/libft.h"
#include "./srcs/Minishell.h"

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
	tmp->next = NULL;
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
			j--;
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
		j++;
	res = ft_substr(s, (*i) + 1, j - (*i + 1));
	(*i) = j;
	return (res);
}

void				ft_space_skip(char *s, int *i)
{
	while (s[*i] == ' ')
		(*i)++;
}

void ft_add_chain(t_list **buff, int *i, char *s, int *len)
{
	int	j;
	t_list	*tmp;
	char	*m;

	j = i;
	while (s[i] && s[*i] != ' ')
		(*i)++;
	m = ft_substr(s, j, *i - j);
	tmp = ft_lstnew(m);
	ft_lstadd_back(&buff, tmp);
	(*len) += ft_strlen(m);
	free(m);
}

char	*ft_remove_spaces(char *s)
{
	t_list	*buff;
	t_list	*tmp;
	char	*res;
	int		len;
	int		i;

	buff = NULL;
	res = NULL;
	i = -1;
	while (s[++i])
	{
		if (s[i] == ' ')
			ft_space_skip(s, &i);
		if (s[i])
			ft_add_chain(&buff, &i, s, &len);
	}
	res = ft_concat(buff, len);
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
	if (j - k == 0)
		return (NULL);
	name = ft_substr(s, k, j - k);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, name, ft_strlen(tmp->key)) == 0)
			res = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	*inc += ft_strlen(name);
	free(name);
	if (s[++j] && flag == 1)
	{
		if (res)
			name = ft_strjoin(res, &s[j]);
		else
			name = ft_strdup(&s[j]);
	}
	else
		return (res);
	free(res);
	return (name);
}

void	ft_listclear(t_list **lst)
{
	t_list *nxt;
	t_list *tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp)
		{
			nxt = (tmp)->next;
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
			tmp = nxt;
		}
		*lst = NULL;
	}
}

int	ft_quoted_str(char *s, int *i, t_list **list, int *len)
{
	int		j;
	char	*res;
	t_list	*tmp;

	j = *i;
	while (s[j] && s[j] != '\"' && s[j] != '\\' && s[j] != '$')
		j++;
	if (!(res = ft_substr(s, *i, j - *i)))
		return (-1);
	if (!(tmp = ft_lstnew(res)))
	{
		free(res);
		return (-2);
	}
	ft_lstadd_back(list, tmp);
	*i = j - 1;
	(*len) += ft_strlen(res);
	return (0);
}

int			ft_dollar(char *s, int *i, t_list **list, int *len)
{
	char	*res;
	int		inc;
	t_list	*tmp;

	if (!(res = ft_search_var(s, &inc, 0, i)))
		return (0);
	if (!(tmp = ft_lstnew(res)))
		return (-1);
	ft_lstadd_back(list, tmp);
	(*i) += inc;
	(*len) += ft_strlen(res);
	return (0);
}

static int	ft_quoted_esc(char *s, int *i, t_list **list, int *len)
{
	char	*res;
	t_list	*tmp;

	(*i)++;
	if (!(s[*i]))
		return (0);
	if (!(res = ft_substr(s, *i, 1)))
		return (-1);
	if (!(tmp = ft_lstnew(res)))
	{
		free(res);
		return (-2);
	}
	ft_lstadd_back(list, tmp);
	(*len) += ft_strlen(res);
	return (0);
}

char	*ft_concat(t_list *list, int len)
{
	t_list	*tmp;
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!(res = ft_calloc(len + 1, sizeof(char))))
	{
		ft_listclear(&list);
		return (NULL);
	}
	tmp = list;
	while (tmp)
	{
		j = 0;
		while (tmp->content[j])
		{
			res[i] = tmp->content[j];
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	ft_listclear(&list);
	return (res);
}

char	*ft_double(char *s, int *i, int *r)
{
	t_list	*list;
	char	*res;
	int		len;

	len = 0;
	list = NULL;
	res = NULL;
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$')
			(*r) = ft_dollar(s, i, &list, &len);
		else if (s[*i] == '\\')
			(*r) = ft_quoted_esc(s, i, &list, &len);
		else
			(*r) = ft_quoted_str(s, i, &list, &len);
		if (*r)
		{
			ft_listclear(&list);
			return (NULL);
		}
		(*i)++;
	}
	if (s[*i] != '\"')
	{
		(*r) = -3;
		ft_listclear(&list);
	}
	if (list)
		res = ft_concat(list, len);
	return (res);
}

/*
**	APPLY FT ACCORDING TO QUOTES OR NOT
*/

char		*ft_apply(char *s, int *i, char *(*f)(char *s, int *i), char *res)
{
	char	*tmp;
	char	*tmp_bis;

	tmp_bis = NULL;
	tmp = (*f)(s, i);
	if (!(res) && tmp)
		tmp_bis = ft_strdup(tmp);
	else if (res && tmp)
		tmp_bis = ft_strjoin(res, tmp);
	free(res);
	res = NULL;
	free(tmp);
	return (tmp_bis);
}

int		ft_apply_double(char *s, int *i, char *(*f)(char *s, int *i, int *r),
						char **res)
{
	char	*tmp;
	char	*tmp_bis;
	int		r;

	r = 0;
	tmp_bis = NULL;
	tmp = (*f)(s, i, &r);
	if (!(*res) && tmp)
		tmp_bis = ft_strdup(tmp);
	else if (*res && tmp)
		tmp_bis = ft_strjoin(*res, tmp);
	free(*res);
	*res = NULL;
	free(tmp);
	*res = tmp_bis;
	return (r);
}

char	*ft_apply_var(char *s, int *i, char *res)
{
	char	*tmp;
	char	*tmp_bis;
	int		inc;

	tmp_bis = NULL;
	tmp_bis = ft_search_var(s, &inc, 0, i);
	(*i) += inc;
	if (!(tmp_bis))
		return (res);
	if (res)
		tmp = ft_strjoin(res, tmp_bis);
	else
	{
		free(res);
		return (tmp_bis);
	}
	free(res);
	return (tmp);
}

/*
**	ADDS STR TO COMMANDS LIST WHEN SPLITTING SPACE IS REACHED
*/
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

void	ft_parse_error(t_list *command)
{
	if (command)
	{
		ft_listclear(&command);
		printf("There's been a malloc error.\n");
	}
}

void	ft_double_error(int r, t_list *command, char *res)
{
	if (res)
		free(res);
	ft_listclear(&command);
	if (r == -3)
		printf("DOUBLE QUOTES NOT CLOSED\n");
	else
		printf("There's been a malloc error.\n");
}

t_list		*ft_parse(char *s)
{
	t_list	*command;
	char	*res;
	int		i;
	int		r;

	r = 0;
	i = -1;
	res = NULL;
	command = NULL;
	while (s[++i])
	{
		if (s[i] != ' ')
		{
			if (s[i] == '\"')
			{
				if (r = ft_apply_double(s, &i, &ft_double, &res))
				{
					ft_double_error(r, command, res);
					return (NULL);
				}
			}
			else if (s[i] == '\'')
				res = ft_apply(s, &i, &ft_single, res);
			else if (s[i] == '$')
				res = ft_apply_var(s, &i, res);
			else
				res = ft_apply(s, &i, &ft_string, res);
			if (!(res))
			{
				ft_parse_error(command);
				return (NULL);
			}
		}
		else if (s[i] == ' ')
		{
			ft_empty_buffer(res, &command);
			free(res);
			res = NULL;
		}
	}
	if (res)
	{
		ft_empty_buffer(res, &command);
		free(res);
		res = NULL;
	}
	return (command);
}

void	ft_free_env(void)
{
	t_env	*tmp;

	while (g_env)
	{
		tmp = g_env->next;
		free(g_env->key);
		free(g_env->value);
		free(g_env);
		g_env = tmp;
	}
}

int	main(void)
{
	char *s;
	t_list	*command;
	t_list	*tmp;

	ft_new_env();
	s = ft_strdup("\"export lol\"lol=value");
	command = ft_parse(s);
	tmp = command;
	while (tmp)
	{
		printf("S IS %s\n", tmp->content);
		tmp = tmp->next;
	}
	printf("%s\n", s);
	
	free(s);
	ft_listclear(&command);
	ft_free_env();
	//ft_env();
	//ft_pwd();
	return (0);
}
