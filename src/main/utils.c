/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:08:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/09 17:33:40 by hakahmed         ###   ########.fr       */
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
	while (1)
	{
		if (line && line[0])
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
		}
		free(line);
		line = readline(prompt);
	}
	free(line);
}

void	destroyer(void)
{
	free(data->cmdtab->cmd);
	ft_lstclear(&(data->cmdtab->args), &free);
	ft_lstclear(&(data->cmdtab->redir_in), &free);
	ft_lstclear(&(data->cmdtab->redir_out), &free);
	ft_lstclear(&(data->tokens), &free);
}
