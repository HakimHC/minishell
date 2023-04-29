/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/29 20:08:39 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#include "minishell.h"

int	handle_heredoc(char *delim)
{
	(void) delim;
	return (0);
}

int	open_infile(t_cmdtab *tab)
{
	t_list *lst;
	t_redir *file;
	int	fd;

	lst = tab->redir_in;
	if (!lst)
		return (STDIN_FILENO);
	file = lst->content;
	while (lst->next)
	{
		file = lst->content;
		if (file->type == HEREDOC)
			fd = handle_heredoc(file->file);
		fd = open(file->file, O_RDONLY);
		if (fd < 0)
			perror(file->file);
		close(fd);
		lst = lst->next;
	}
	if (file->type == REDIR_IN)
	{
		fd = open(file->file, O_RDONLY);
		if (fd < 0)
			perror_exit(file->file);
	}
	else
		fd = handle_heredoc(file->file);
	return (fd);
}

int	open_with_flags(char *file, int type)
{
	int	flags;
	int	fd;

	flags = O_CREAT | O_WRONLY;
	if (type == REDIR_OUT)
		flags = flags | O_TRUNC;
	if (type == APPEND)
		flags = flags | O_APPEND;
	fd = open(file, flags, 0644);
	return (fd);

}

int	open_outfile(t_cmdtab *tab)
{
	t_list *lst;
	t_redir *file;
	int	fd;

	lst = tab->redir_out;
	if (!lst)
		return (STDOUT_FILENO);
	file = lst->content;
	while (lst->next)
	{
		fd = open_with_flags(file->file, file->type);
		if (fd < 0)
			perror(file->file);
		close(fd);
		lst = lst->next;
	}
	fd = open_with_flags(file->file, file->type);
	if (fd < 0)
		perror_exit(file->file);
	return (fd);
}

void	create_pipe(int redir_out, t_cmdtab *tab)
{
	int	fd[2];
	pid_t	pid;

	pipe(fd);
	pid = ft_fork();
	if (!pid)
	{
		close(fd[READ_END]);
		if (redir_out != STDOUT_FILENO)
			dup2(redir_out, STDOUT_FILENO);
		else
			dup2(fd[WRITE_END], STDOUT_FILENO);
		ft_execute(tab->cmd, tab->args);
	}
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}

void	executor(t_cmdtab *tab)
{
	int	fdin;
	int	fdout;
	
	if (!tab)
		return ;
	dprintf(2, "executor init\n");
	fdin = open_infile(tab);
	/* dup2(fdin, STDIN_FILENO); */
	fdout = open_outfile(tab);
	if (tab->next)
		create_pipe(fdout, tab);
	else
	{
		/* dup2(fdout, STDOUT_FILENO); */
		if (!fork())
		{
			dup2(fdout, STDOUT_FILENO);
			dup2(fdin, STDIN_FILENO);
			ft_execute(tab->cmd, tab->args);
		}
		wait(NULL);
		return ;
	}
	executor(tab->next);
}
