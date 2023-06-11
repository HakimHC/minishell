/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 01:47:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/11 04:36:48 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

char *expand(char *token)
{
	t_list *tmp;
	char *content;

	tmp = NULL;
	if (!ft_strchr(token, '$'))
		return (token);
	content = token;
	int i = 0;
	int j;
	t_list *node;
	while (content[i])
	{
		j = 0;
		if (content[i] == '$')
		{
			i++;
			while (content[i + j] && content[i + j] != '$'
				&& !ft_isspace(content[i + j]))
				j++;
			node = ft_lstnew(ft_substr(content, i - 1, j + 1));
			/* ft_printf("{%s}\n", node->content); */
			ft_lstadd_back(&tmp, node);
			i += j;
		}
		else
		{
			while (content[i + j] && content[i + j] != '$')
				j++;
			node = ft_lstnew(ft_substr(content, i, j));
			/* ft_printf("{%s}\n", node->content); */
			ft_lstadd_back(&tmp, node);
			i += j;
		}
	}
	t_list *curr = tmp;
	while (curr)
	{
		if (ft_strchr(curr->content, '$') && ft_strncmp(curr->content, "$", 2))
		{
			char *aux = curr->content;
			if (ft_getenv(curr->content + 1))
				curr->content = ft_strdup(ft_getenv(curr->content + 1));
			else if (!ft_strncmp(curr->content, "$?", 3))
				curr->content = ft_itoa(g_data->exit_code);
			else
				curr->content = NULL;
			free(aux);
		}
		curr = curr->next;
	}
	char *res = ft_strdup("");
	curr = tmp;
	while (curr)
	{
		char *aux = res;
		if (curr->content)
			res = ft_strjoin(res, curr->content);
		else
			res = ft_strjoin(res, "");
		free(aux);
		curr = curr->next;
	}
	free(content);
	ft_lstclear(&tmp, free);
	return (res);
}

