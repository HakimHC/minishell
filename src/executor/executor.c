/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/21 01:01:17 by hakahmed         ###   ########.fr       */
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

#include "libft.h"
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

void	hnd_exitcode(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_data->exit_code = 130;
		if (WTERMSIG(status) == 3)
		{
			g_data->exit_code = 131;
			ft_putstr_fd("Quit (core dumped)", 2);
		}
		write(1, "\n", 2);
	}
	else
		g_data->exit_code = WEXITSTATUS(status);
}

void	executor(t_cmdtab *tab)
{
	pid_t	pid;
	int		status;

	if (g_data->sig_hd)
		return ;
	if (!(tab->next) && is_builtin(tab->cmd))
		handle_builtin(&tab);
	else
	{
		pid = ft_fork();
		if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			while (tab)
				tab = smart_exec(tab);
			wait_childs();
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		hnd_exitcode(status);
	}
	sighandler();
}
