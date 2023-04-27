/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:49:30 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/27 16:42:18 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

t_cmdtab	*cmdtab_init(void)
{
	t_cmdtab	*tab;

	tab = (t_cmdtab *) malloc(sizeof(t_cmdtab));
	if (!tab)
		return (NULL);
	tab = ft_memset(tab, 0, sizeof(t_cmdtab));
	return (tab);
}

int	*set_flags(t_data *data)
{
	int	*flags;
	t_list	*curr;

	flags = (int *) malloc(sizeof(int));
	if (!flags)
		return (NULL);
	*flags = 0;
	curr = data->tokens;
	while (curr && ft_strncmp(curr->content, "|", 1))
	{
		if (!ft_strncmp(curr->content, "<<", 2))
			*flags = *flags | HEREDOC;
		else if (!ft_strncmp(curr->content, ">>", 2))
			*flags = *flags | APPEND;
		else if (!ft_strncmp(curr->content, ">", 1))
			*flags = *flags | REDIR_OUT;
		else if (!ft_strncmp(curr->content, "<", 1))
			*flags = *flags | REDIR_IN;
		curr = curr->next;
	}
	return (flags);
}

void	make_redir(t_data *data, int type, char *file)
{
	t_redir	*redir;

	redir = (t_redir *) malloc(sizeof(t_redir));
	// PROTECT MALLOC
	if (!redir)
		return ;
	redir->type = type;
	redir->file = ft_strdup(file);
	if (type == REDIR_OUT || type == APPEND)
		ft_lstadd_back(&(data->cmdtab->redir_out), ft_lstnew(redir));
	else if (type == REDIR_IN || type == HEREDOC)
		ft_lstadd_back(&(data->cmdtab->redir_in), ft_lstnew(redir));
	else
		ft_putstr_fd("fatal: bad redirection\n", 2);
}

void	populate(t_data *data)
{
	t_list	*curr;

	curr = data->tokens;
	while (curr && ft_strncmp(curr->content, "|", 1))
	{
		if (!ft_strncmp(curr->content, "<<", 2))
		{
			curr = curr->next;
			ft_lstadd_back(&(data->cmdtab->redir_in), ft_lstnew(ft_strdup(curr->content)));
			*(data->cmdtab->flags) = *(data->cmdtab->flags) & ~REDIR_IN;
		}
		else if (!ft_strncmp(curr->content, ">>", 2))
		{
			curr = curr->next;
			ft_lstadd_back(&(data->cmdtab->redir_out), ft_lstnew(ft_strdup(curr->content)));
			*(data->cmdtab->flags) = *(data->cmdtab->flags) & ~REDIR_OUT;

		}
		else if (!ft_strncmp(curr->content, ">", 1))
		{
			curr = curr->next;
			ft_lstadd_back(&(data->cmdtab->redir_out), ft_lstnew(ft_strdup(curr->content)));
			*(data->cmdtab->flags) = *(data->cmdtab->flags) & ~APPEND;
		}
		else if (!ft_strncmp(curr->content, "<", 1))
		{
			curr = curr->next;
			ft_lstadd_back(&(data->cmdtab->redir_in), ft_lstnew(ft_strdup(curr->content)));
			*(data->cmdtab->flags) = *(data->cmdtab->flags) & ~HEREDOC;
		}
		else if (ft_strncmp(curr->content, "|", 1) && !data->cmdtab->cmd)
		{
			data->cmdtab->cmd = ft_strdup(curr->content);
		}
		else if (ft_strncmp(curr->content, "|", 1))
		{
			ft_lstadd_back(&(data->cmdtab->args), ft_lstnew(ft_strdup(curr->content)));
		}
		curr = curr->next;
	}
}
