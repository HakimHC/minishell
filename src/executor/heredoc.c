/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:19:41 by hakim             #+#    #+#             */
/*   Updated: 2023/06/23 04:51:32 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "minishell.h"

void	p_warning(char *delim)
{
	ft_printf("warning: here-document delimited by end-of-file (wanted `%s')\n",
		delim);
}

int	handle_heredoc(char *delim)
{
	int		fd;
	char	*line;
	pid_t	pid;
	int		status;

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	pid = ft_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (!line)
			p_warning(delim);
		while (line && ft_strncmp(line, delim, ft_strlen(line) + 1))
		{
			line = expand(line);
			ft_putendl_fd(line, fd);
			free(line);
			line = readline("> ");
			if (!line)
				p_warning(delim);
		}
		free(line);
		close(fd);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			write(1, "\n", 1);
			g_data->sig_hd = 1;
		}
	}
	return (fd);
}
