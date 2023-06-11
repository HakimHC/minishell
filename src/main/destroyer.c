/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 03:43:18 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/11 04:40:07 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

void	free_redirs(t_list *redirs)
{
	t_redir	*curr;

	while (redirs)
	{
		curr = redirs->content;
		free(curr->file);
		redirs = redirs->next;
	}
}

void	free_tokens(void)
{
	t_list	*curr;
	t_token	*tkn;

	curr = g_data->tokens;
	while (curr)
	{
		tkn = curr->content;
		free(tkn->content);
		curr = curr->next;
	}
	ft_lstclear(&(g_data->tokens), free);
}

void	free_cmdtab(void)
{
	t_cmdtab	*curr;
	t_cmdtab	*aux;

	curr = g_data->cmdtab;
	while (curr)
	{
		aux = curr;
		free(curr->cmd);
		ft_lstclear(&(curr->args), &free);
		free_redirs(curr->redir_in);
		free_redirs(curr->redir_out);
		ft_lstclear(&(curr->redir_in), &free);
		ft_lstclear(&(curr->redir_out), &free);
		curr = curr->next;
		free(aux);
	}
	g_data->cmdtab = NULL;
}

void	destroyer(void)
{
	free_cmdtab();
	free_tokens();
}
