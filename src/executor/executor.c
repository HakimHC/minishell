/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/01 17:14:34 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "minishell.h"

int	handle_heredoc(char *delim)
{
	int	fd;
	char	*line;
	pid_t pid;

	line = readline("heredoc> ");
	fd = ft_open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC);
	pid = ft_fork();
	if (!pid)
	{
		while (ft_strncmp(line, delim, ft_strlen(line)))
		{
			ft_putendl_fd(line, fd);
			free(line);
			line = readline("heredoc> ");
		}
		free(line);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	return (fd);
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
	while (lst)
	{
		file = lst->content;
		if (file->type == HEREDOC)
			fd = handle_heredoc(file->file);
		else
			fd = open(file->file, O_RDONLY);
		if (fd < 0)
			perror(file->file);
		if (lst->next)
			close(fd);
		lst = lst->next;
	}
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
	while (lst)
	{
		file = lst->content;
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

void	create_pipe(int redir_out, int redir_in, t_cmdtab *tab)
{
	int	fd[2];
	pid_t	pid;

	pipe(fd);
	pid = ft_fork();
	if (!pid)
	{
		close(fd[READ_END]);
		if (redir_in != STDIN_FILENO)
		{
			dup2(redir_in, STDIN_FILENO);
			/* close(redir_in); */
		}
		if (redir_out != STDOUT_FILENO)
		{
			dup2(redir_out, STDOUT_FILENO);
			/* close(redir_out); */
		}
		else
			dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		ft_execute(tab->cmd, tab->args);
		exit(0);
	}
	/* close(redir_in); */
	/* close(redir_out); */
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}

void	executor(t_cmdtab *tab)
{
	int	fdin;
	int	fdout;
	pid_t	pid;
	int	status;

	if (!tab)
		return;
	pid = ft_fork();
	if (!pid)
	{
		while (tab)
		{
			fdin = open_infile(tab);
			fdout = open_outfile(tab);
			if (fdin < 0 || fdout < 0)
			{
				tab = tab->next;
				continue;
			}
			if (tab->next)
				create_pipe(fdout, fdin, tab);
			else
			{
				/* dup2(fdout, STDOUT_FILENO); */
				dup2(fdout, STDOUT_FILENO);
				dup2(fdin, STDIN_FILENO);
				if (fdin != STDIN_FILENO)
					close(fdin);
				if (fdout != STDOUT_FILENO)
					close(fdout);
				ft_execute(tab->cmd, tab->args);
				while (1)
				{
					pid_t p = waitpid(-1, &status, 0);
					if (p < 0)
						exit(WEXITSTATUS(status));
				}
				exit(WEXITSTATUS(status));
			}
			tab = tab->next;
		}

	}
	waitpid(pid, &status, 0);
}
