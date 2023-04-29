/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:08:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/29 23:23:55 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

void	cmd_listen(char *prompt)
{
	char	*line;

	line = readline(prompt);
	while (ft_strncmp(line, "exit", 4))
	{
		if (line[0])
		{
			add_history(line);
			if (pre_token_parse_error(line))
			{
				print_token_error("|");
				exit(1);
			}
			if (!tokenize_input(line))
			{
				fill_cmdtab();
				/* print_cmdtab(); */
				executor(data->cmdtab);
			}
			/* destroyer(); */
		}
		free(line);
		line = readline(prompt);
	}
	free(line);
}

void	destroyer(void)
{
	// !!!!!!!!!! FREEE REDIRS IN LOOP

	free(data->cmdtab->cmd);
	ft_lstclear(&(data->cmdtab->args), &free);
	if (data->cmdtab->redir_in && data->cmdtab->redir_in->content)
		free((char*)((t_redir *)(data->cmdtab->redir_in->content))->file);
	if (data->cmdtab->redir_out &&data->cmdtab->redir_out->content)
		free((char*)((t_redir *)(data->cmdtab->redir_out->content))->file);
	ft_lstclear(&(data->cmdtab->redir_in), &free);
	ft_lstclear(&(data->cmdtab->redir_out), &free);
	ft_lstclear(&(data->tokens), &free);
}

