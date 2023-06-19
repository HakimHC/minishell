/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 01:47:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/19 22:33:14 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

int	mk_exptoken(t_list **head, char *token, int i)
{
	t_list	*node;
	int		j;

	i++;
	j = 0;
	while (token[i + j] && token[i + j] != '$'
		&& (ft_isalnum(token[i + j]) || token[i + j] == '?'))
		j++;
	node = ft_lstnew(ft_substr(token, i - 1, j + 1));
	ft_lstadd_back(head, node);
	return (j + 1);
}

void	split_envars(t_list **head, char *token)
{
	int		i;
	int		j;
	t_list	*node;

	i = 0;
	while (token[i])
	{
		j = 0;
		if (token[i] == '$')
			i += mk_exptoken(head, token, i);
		else
		{
			while (token[i + j] && token[i + j] != '$')
				j++;
			node = ft_lstnew(ft_substr(token, i, j));
			ft_lstadd_back(head, node);
			i += j;
		}
	}
}

void	expand_env(t_list *head)
{
	t_list	*curr;
	char	*aux;

	curr = head;
	while (curr)
	{
		if (ft_strchr(curr->content, '$') && !ft_strncmp(curr->content, "$", 1))
		{
			aux = curr->content;
			if (!ft_strncmp(curr->content, "$?", 3))
				curr->content = ft_itoa(g_data->exit_code);
			else if (ft_getenv(curr->content + 1))
				curr->content = ft_strdup(ft_getenv(curr->content + 1));
			else
				curr->content = NULL;
			free(aux);
		}
		curr = curr->next;
	}
}

char	*expand(char *token)
{
	t_list	*tmp;
	t_list	*curr;
	char	*aux;
	char	*res;

	if (!ft_strchr(token, '$'))
	{
		aux = ft_strdup(token);
		return (free(token), aux);
	}
	tmp = NULL;
	split_envars(&tmp, token);
	expand_env(tmp);
	res = ft_strdup("");
	curr = tmp;
	while (curr)
	{
		aux = res;
		if (curr->content)
			res = ft_strjoin(res, curr->content);
		else
			res = ft_strjoin(res, "");
		free(aux);
		curr = curr->next;
	}
	free(token);
	ft_lstclear(&tmp, free);
	return (res);
}
