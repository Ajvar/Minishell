/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:12:48 by jcueille          #+#    #+#             */
/*   Updated: 2021/03/05 13:31:37 by jcueille         ###   ########.fr       */
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

void ft_new_env()
{
	g_env = malloc(sizeof(t_env));
	g_env->key = ft_strdup("VAR");
	g_env->value = ft_strdup("VALUE");
	t_env *tmp;
	tmp = malloc(sizeof(t_env));
	g_env->next = tmp;
	tmp->key = ft_strdup("VARZ");
	tmp->value = ft_strdup("VALUZ");
}

//REMOVE A SINGLE CHAR FROM A STRING
static void	ft_remove_char(char *s, int i)
{
	char	*res;
	int		j;

	if (!(res = malloc(ft_strlen(s)  * sizeof(char))))
		return ;
	j = -1;
	while(++j < i)
		res[j] = s[j];
	i = j;
	while(s[++j])
	{
		res[i] = s[j];
		i++;
	}
	res[j - 1] = '\0'; 
	free(s);
	s = ft_strdup(res);
	free(res);
}

//CHECKS IF VAR BRACKETS ARE CLOSED
static int ft_bracket_check(char *s, int i)
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

static void ft_error()
{
	printf("error\n");
	exit(1);
}

static void ft_expand(char *s, int i)
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







// STRING SANS QUOTES
static char	*ft_string(char *s, int *i)
{
	int		j;
	//t_list	*tmp;
	char	*res;

	j = *i;
	while(s[j] && s[j] != ' ' && s[j] != '\"' && s[j] != '\'' && s[j] != '$')
	{
		if (s[j] == '\\')
			ft_remove_char(s, j);
		j++;
	}
	res = ft_substr(s, *i, j - *i);
	//tmp = ft_lstnew(res);
	//ft_lstadd_back(&command, tmp);
	(*i) = j - 1;
	return (res);
}

static char	*ft_single(char *s, int *i)
{
	int		j;
	//t_list	*tmp;
	char	*res;

	j = (*i) + 1;
	while(s[j] && s[j] != '\'')
	{
		if (s[j] == '\\')
			ft_remove_char(s, j);
		j++;
	}
	res = ft_substr(s, (*i) + 1, j - (*i + 1));
	//ft_lstadd_back(&command, tmp);
	(*i) = j;
	return (res);
}

//RETRIEVE VAR VALUE
static char	*ft_search_var(char *s, int *inc, int flag, int *i)
{
	//int		i;
	int		k;
	int		j;
	t_env	*tmp;
	char	*name;
	char	*res;

	//i = 1;
	k = *i;
	
	(*inc) = 0;
	tmp = g_env;
	res = NULL;
	if (!(s[i]))
		return (res);
	if (s[i] == '{')
	{
		if (!(ft_bracket_check(s, i)))
			return (res);
		(*inc) += 2;
		i++;
	}
	j = i;
	while (s[j] && s[j] != ' ' && s[j] != '}')
		j++;
		name = ft_substr(s, i, j - i);
	while (tmp)
	{
		//if (ft_strncmp(tmp->key, name, ft_strlen(tmp->key)) == 0)
		//	res = ft_strdup(tmp->value);
		int l = ft_strncmp(tmp->key, name, ft_strlen(tmp->key));
		if (l == 0)
			res = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	*inc += ft_strlen(name);
	free(name);
	if (s[1] != '{')
		(*inc) -= 2;
	if (s[++j] && flag == 1)
		name = ft_strjoin(res, &s[j]);
	else
		return (res);
	free(res);
	return (name);
}


//DOLLAR DANS QUOTES
static char	*ft_dollar(char *s, int *i, int *j)
{
	char	*tmp;
	char	*var;
	int		inc;

	var = ft_search_var(&s[*j], &inc, 1);
	s[*j] = '\0';
	*j = inc;
	tmp = ft_strjoin(s, var);
	//free(s);
	//s = ft_strdup(tmp);
	return (tmp);
}


// DOUBLE QUOTES
static char *ft_double(char *s, int *i)
{
	int j;
	char *res;

	//ft_remove_char(s, *i);
	(*i)++;
	j = *i;
	if (!(s[*i]))
		return NULL;
	while (s[j] && s[j] != '\"')
	{
		if (s[j] == '\\')
		{	
			if (s[j + 1] == '\\' || s[j + 1] == '\"')
			{
				ft_remove_char(s, j);
				j++;
			}
		}
		if (s[j] == '$')
			s = ft_dollar(s, i, &j);
		j++;
	}
	if (s[j] == '\0')
		printf("ftprompt");
	//²else
	//ft_remove_char(s, j);	
		//remove " et check si on a une string après, si on a space ou \0 on arrete sinon on append.
	
	res = ft_substr(s, *i, j - (*i + 1));
	(*i) = j + 1;
	return (res);
}

//APPLY FT ACCORDING TO QUOTES OR NOT
char	*ft_apply_ft(char *s, int *i, char *(*f)(char *s, int *i), char *res)
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
void ft_empty_buffer(char *s, t_list **command)
{
	t_list	*tmp;
	char	*copy;

	if (!(s))
		return ;
	copy = ft_strdup(s);
	tmp = ft_lstnew(copy);
	ft_lstadd_back(command, tmp);
	//if (s)
	//{	
	//	free(s);
	//	s = NULL;
	//}
}

t_list *ft_parse(char *s)
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
			res = ft_apply_ft(s, &i, &ft_double, res);
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
			res = ft_apply_ft(s, &i, &ft_single, res);
			continue;
		}
		else if (s[i] == '$')
		{
			res = ft_search_var(&s[i], &inc, 0);
			i += inc;
		}
		else
			res = ft_apply_ft(s, &i, &ft_string, res);
	}
	if (res)
		ft_empty_buffer(res, &command);
	while (command)
	{
		printf("S IS %s\n", command->content);
		command = command->next;
	}
}

int main()
{
	// t_list *command;
	char *s;
	ft_new_env();
	s = ft_strdup("\"${VAR}\" \"\'lol\'\" ${VR} mdr");
	int n = 0;
	int k = 5;
	int *j = &k;
	int *i = &n;
	
	ft_parse(s);
	printf("%s\n", s);
	// command = ft_parse(s);
	//int i =0;

	//while (res[i])
	//{
	//	printf("%s", res[i]);
	//	i++;
	//}
	return 0;
}