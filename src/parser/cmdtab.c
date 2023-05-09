/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:49:30 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/09 13:31:18 by hakahmed         ###   ########.fr       */
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

void	make_redir(t_data *data, int type, char *file, t_cmdtab *tab)
{
	t_redir	*redir;

	(void) data;
	redir = (t_redir *) malloc(sizeof(t_redir));
	if (!redir)
		perror_exit("malloc");
	redir->type = type;
	redir->file = ft_strdup(file);
	if (type == REDIR_OUT || type == APPEND)
		ft_lstadd_back(&(tab->redir_out), ft_lstnew(redir));
	else if (type == REDIR_IN || type == HEREDOC)
		ft_lstadd_back(&(tab->redir_in), ft_lstnew(redir));
	else
		ft_putstr_fd("fatal: bad redirection\n", 2);
}

unsigned char	handle_redirs(t_list *curr, t_cmdtab *curr_cmd)
{
	if (!ft_strncmp(curr->content, "<<", 2))
	{
		curr = curr->next;
		make_redir(data, HEREDOC, curr->content, curr_cmd);
	}
	else if (!ft_strncmp(curr->content, ">>", 2))
	{
		curr = curr->next;
		make_redir(data, APPEND, curr->content, curr_cmd);
	}
	else if (!ft_strncmp(curr->content, ">", 1))
	{
		curr = curr->next;
		make_redir(data, REDIR_OUT, curr->content, curr_cmd);
	}
	else if (!ft_strncmp(curr->content, "<", 1))
	{
		curr = curr->next;
		make_redir(data, REDIR_IN, curr->content, curr_cmd);
	}
	else
		return (0);
	return (1);
}

t_list	*determine_type(t_list *curr, t_cmdtab *curr_cmd)
{
	if (handle_redirs(curr, curr_cmd))
		curr = curr->next;
	else if (ft_strncmp(curr->content, "|", 1) && !curr_cmd->cmd)
		curr_cmd->cmd = ft_strdup(curr->content);
	else if (ft_strncmp(curr->content, "|", 1))
		ft_lstadd_back(&(curr_cmd->args),
			ft_lstnew(ft_strdup(curr->content)));
	return (curr);
}

void	populate(t_data *data)
{
	t_list		*curr;
	t_cmdtab	*curr_cmd;

	curr = data->tokens;
	curr_cmd = data->cmdtab;
	while (curr)
	{
		while (curr && ft_strncmp(curr->content, "|", 1))
		{
			curr = determine_type(curr, curr_cmd);
			curr = curr->next;
		}
		if (curr && !ft_strncmp(curr->content, "|", 1))
		{
			curr_cmd->next = cmdtab_init();
			curr_cmd = curr_cmd->next;
		}
		if (curr)
			curr = curr->next;
	}
}
