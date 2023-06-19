/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/19 19:34:40 by hakahmed         ###   ########.fr       */
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

	sighandler();
	if (!(tab->next) && is_builtin(tab->cmd))
		handle_builtin(&tab);
	else
	{
		pid = ft_fork();
		if (!pid)
		{
			signal(SIGINT, &handle_sigint);
			signal(SIGQUIT, SIG_DFL);
			while (tab)
				tab = smart_exec(tab);
			if (WIFSIGNALED(SIGINT))
				write(1, "\n", 1);
			wait_childs();
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WTERMSIG(status) + 128 == 130)
			write(1, "\n", 1);
		g_data->exit_code = WEXITSTATUS(status);
	}
	sighandler();
}
