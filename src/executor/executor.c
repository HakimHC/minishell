/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/17 03:31:11 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "minishell.h"

t_cmdtab	*smart_exec(t_cmdtab *tab)
{
	int	fdin;
	int	fdout;

	fdout = open_outfile(tab);
	fdin = open_infile(tab);
	if (tab->next)
		create_pipe(fdout, fdin, tab);
	else
		exec_last(fdin, fdout, tab);
	tab = tab->next;
	return (tab);
}

void	executor(t_cmdtab *tab)
{
	pid_t	pid;
	int		status;

	/* signal(SIGINT, &sigint_cmd); */
	if (!(tab->next) && is_builtin(tab->cmd))
		handle_builtin(&tab);
	else
	{
		pid = ft_fork();
		if (!pid)
		{
			while (tab)
				tab = smart_exec(tab);
			wait_childs();
		}
		sighandler();
		waitpid(pid, &status, 0);
		g_data->exit_code = WEXITSTATUS(status);
	}
}
