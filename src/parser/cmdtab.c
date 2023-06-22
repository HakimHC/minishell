/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:49:30 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/22 04:23:39 by hakahmed         ###   ########.fr       */
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
	if (type == HEREDOC)
	{
		redir->type = REDIR_IN;
		redir->file = ft_strdup("/tmp/.heredoc");
		ft_lstadd_back(&(tab->redir_in), ft_lstnew(redir));
		handle_heredoc(file);
		return ;
	}
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
	t_token		*tkn;
	static char	*symbols[] = {"<", "<<", ">", ">>"};
	static int	types[] = {REDIR_IN, HEREDOC, REDIR_OUT, APPEND};
	int			i;

	tkn = curr->content;
	if (tkn->type != SYMB)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(tkn->content, symbols[i], ft_strlen(symbols[i]) + 1))
		{
			curr = curr->next;
			tkn = curr->content;
			make_redir(g_data, types[i], tkn->content, curr_cmd);
			return (1);
		}
		++i;
	}
	return (0);
}

t_list	*determine_type(t_list *curr, t_cmdtab *curr_cmd)
{
	if (handle_redirs(curr, curr_cmd))
		curr = curr->next;
	else if (!curr_cmd->cmd)
		curr_cmd->cmd = ft_strdup(((t_token *)curr->content)->content);
	else
		ft_lstadd_back(&(curr_cmd->args),
			ft_lstnew(ft_strdup(((t_token *)curr->content)->content)));
	return (curr->next);
}

void	populate(t_data *data)
{
	t_list		*curr;
	t_token		*tkn;
	t_cmdtab	*curr_cmd;

	curr = data->tokens;
	curr_cmd = data->cmdtab;
	while (curr)
	{
		tkn = curr->content;
		while ((curr && ft_strncmp(tkn->content, "|", 2))
			|| (curr && !ft_strncmp(tkn->content, "|", 2) && tkn->type == NORM))
		{
			curr = determine_type(curr, curr_cmd);
			if (data->sig_hd)
				return ;
			if (curr)
				tkn = curr->content;
		}
		if (curr)
			tkn = curr->content;
		if (curr && !ft_strncmp(tkn->content, "|", 2) && tkn->type == SYMB)
		{
			curr_cmd->next = cmdtab_init();
			curr_cmd = curr_cmd->next;
		}
		curr = p_increment(curr);
	}
}
