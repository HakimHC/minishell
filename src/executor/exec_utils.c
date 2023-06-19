/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:50:32 by hakim             #+#    #+#             */
/*   Updated: 2023/06/19 19:34:33 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

#include "minishell.h"

void	handle_redirects(int redir_out, int redir_in, int pfd)
{
	if (redir_in != STDIN_FILENO)
	{
		dup2(redir_in, STDIN_FILENO);
		close(redir_in);
	}
	if (redir_out != STDOUT_FILENO)
	{
		dup2(redir_out, STDOUT_FILENO);
		close(redir_out);
	}
	else
		dup2(pfd, STDOUT_FILENO);
}

void	create_pipe(int redir_out, int redir_in, t_cmdtab *tab)
{
	int		fd[2];
	pid_t	pid;

	ft_pipe(fd);
	pid = ft_fork();
	if (!pid)
	{
		close(fd[READ_END]);
		handle_redirects(redir_out, redir_in, fd[WRITE_END]);
		close(fd[WRITE_END]);
		ft_execute(tab->cmd, tab->args);
	}
	if (redir_in != STDIN_FILENO)
		close(redir_in);
	if (redir_out != STDOUT_FILENO)
		close(redir_out);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}

unsigned char	handle_builtin(t_cmdtab **tab)
{
	int				tmpin;
	int				fdin;
	int				tmpout;
	int				fdout;
	unsigned char	b;

	fdin = open_infile(g_data->cmdtab);
	fdout = open_outfile(g_data->cmdtab);
	if (fdin < 0 || fdout < 0)
		return (-1);
	tmpin = dup(STDIN_FILENO);
	tmpout = dup(STDOUT_FILENO);
	if (fdin != STDIN_FILENO)
		dup2(fdin, STDIN_FILENO);
	if (fdout != STDOUT_FILENO)
		dup2(fdout, STDOUT_FILENO);
	b = exec_builtin(g_data->cmdtab->cmd, g_data->cmdtab->args);
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	*tab = (*tab)->next;
	g_data->exit_code = 0;
	return (b);
}

void	wait_childs(void)
{
	int		status;
	pid_t	p;

	while (1)
	{
		p = waitpid(-1, &status, 0);
		if (p < 0)
			exit(WEXITSTATUS(status));
	}
}

void	exec_last(int fdin, int fdout, t_cmdtab *tab)
{
	if (!ft_fork())
	{
		if (fdin < 0 || fdout < 0)
			exit(errno);
		if (fdin != STDIN_FILENO)
			dup2(fdin, STDIN_FILENO);
		if (fdout != STDOUT_FILENO)
			dup2(fdout, STDOUT_FILENO);
		if (fdin != STDIN_FILENO)
			close(fdin);
		if (fdout != STDOUT_FILENO)
			close(fdout);
		ft_execute(tab->cmd, tab->args);
	}
	close(fdin);
	close(fdout);
	close(STDIN_FILENO);
}
