/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/13 21:54:12 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "minishell.h"

void	executor(t_cmdtab *tab)
{
	int	fdin;
	int	fdout;
	pid_t	pid;
	int	status;

	if (!(tab->next) && is_builtin(tab->cmd))
		handle_builtin(&tab);
	pid = ft_fork();
	if (!pid)
	{
		while (tab)
		{
			fdout = open_outfile(tab);
			fdin = open_infile(tab);
			if (tab->next)
				create_pipe(fdout, fdin, tab);
			else
				exec_last(fdin, fdout, tab);
			tab = tab->next;
		}
		wait_childs();
	}
	waitpid(pid, &status, 0);
}
