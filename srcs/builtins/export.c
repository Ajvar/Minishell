/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:38:43 by jcueille          #+#    #+#             */
/*   Updated: 2021/03/24 16:58:46 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../Minishell.h"

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



int		ft_search_value(t_list *cmd, char **key)
{
	t_list	*l;
	t_list	*tmp;
	t_list	*buff;
	int		i;
	int		j;

	l = cmd;
	buff = NULL;
	while (l)
	{
		i = 0;
		while (l->content[i] && l->content[i] != '=' && l->content[i] != ' ')
			i++;
		if (l->content[i] == '=')
		{
			if (!(buff))
			{
				if (!(*key = ft_substr(l->content, 0, i - 1)))
					return (-1);
				return (0);
			}
			if (!(tmp = ft_lstnew(key)))
				return (-2);
			ft_lstadd_back(&buff, tmp);
			if (!(*key = ft_concat(buff)))
				return (-3);
			return (0);
		}
		else if (l->content[i] == ' ')
		{
			if (buff)
				ft_listclear(&buff);
		}
		else
		{
			if (!(*key = ft_substr(l->content, 0, i - 1)))
				return (-1);
			return (0);
		}
		if (!(tmp = ft_lstnew(key)))
			return (-2);
		ft_lstadd_back(&buff, tmp);
		l = l->next;
	}
}


void	ft_export(t_list *cmd)
{
	t_env	*tmp;
	char	*key;
	int		i;
	int		j;

	i = -1;
	key = NULL;
	tmp = g_env;
	ft_search_value(cmd, &key);
}
