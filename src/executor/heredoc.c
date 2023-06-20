/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:19:41 by hakim             #+#    #+#             */
/*   Updated: 2023/06/20 10:27:54 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>

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

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	line = readline("heredoc> ");
	if (!line)
		p_warning(delim);
	while (line && ft_strncmp(line, delim, ft_strlen(line) + 1))
	{
		line = expand(line);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("heredoc> ");
		if (!line)
			p_warning(delim);
	}
	free(line);
	close(fd);
	return (fd);
}
