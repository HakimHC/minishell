/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/12 20:48:12 by hakim            ###   ########.fr       */
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

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	line = readline("heredoc> ");
	/* if (!line) */
	/* 	return -1; */
	while (ft_strncmp(line, delim, ft_strlen(line) + 1))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(fd);
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
	while (lst)
	{
		file = lst->content;
		if (file->type == HEREDOC)
			fd = handle_heredoc(file->file);
		else
			fd = open(file->file, O_RDONLY);
		if (fd < 0)
			perror(file->file);
		if (lst->next && fd > 0)
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

	ft_pipe(fd);
	pid = ft_fork();
	if (!pid)
	{
		close(fd[READ_END]);
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
			dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		ft_execute(tab->cmd, tab->args);
		/* exit(0); */
	}
	/* if (redir_in != STDIN_FILENO) */
	/* 	close(redir_in); */
	/* if (redir_out != STDOUT_FILENO) */
	/* 	close(redir_out); */
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}

unsigned char handle_builtin(void)
{
	int	tmpin;
	int	fdin;
	int	tmpout;
	int	fdout;
	unsigned char b;

	tmpin = dup(STDIN_FILENO);
	tmpout = dup(STDOUT_FILENO);
	fdin = open_infile(data->cmdtab);
	fdout = open_outfile(data->cmdtab);
	if (fdin != STDIN_FILENO)
		dup2(fdin, STDIN_FILENO);
	if (fdout != STDOUT_FILENO)
		dup2(fdout, STDOUT_FILENO);
	b = exec_builtin(data->cmdtab->cmd, data->cmdtab->args);
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	return (b);
}

unsigned char is_builtin(char *cmd)
{
	int	i;
	char	*str;

	if (!cmd)
		return (0);
	i = 0;
	while (i < 7)
	{
		str = (data->builtins->cmd)[i];
		if (!ft_strncmp(cmd, str, ft_strlen(cmd) + 1))
			return (1);
		i++;
	}
	return (0);
}

void	executor(t_cmdtab *tab)
{
	int	fdin;
	int	fdout;
	pid_t	pid;
	int	status;

	if (!tab)
		return;
	if (!(tab->next) && is_builtin(tab->cmd))
	{
		handle_builtin();
		tab = tab->next;
	}
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
			{
				if (fdin < 0 || fdout < 0)
					break ;
				if (fdin != STDIN_FILENO)
					dup2(fdin, STDIN_FILENO);
				if (fdout != STDOUT_FILENO)
					dup2(fdout, STDOUT_FILENO);
				if (fdin != STDIN_FILENO)
					close(fdin);
				if (fdout != STDOUT_FILENO)
					close(fdout);
				if (!ft_fork())
					ft_execute(tab->cmd, tab->args);
				close(STDIN_FILENO);
			}
			tab = tab->next;
		}
		while (1)
		{
			pid_t p = waitpid(-1, &status, 0);
			if (p < 0)
				exit(90);
		
		}
	}
	waitpid(pid, NULL, 0);
}
