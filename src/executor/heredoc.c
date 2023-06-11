/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:19:41 by hakim             #+#    #+#             */
/*   Updated: 2023/06/11 17:56:03 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>

#include "minishell.h"

int	handle_heredoc(char *delim)
{
	int		fd;
	char	*line;

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	line = readline("heredoc> ");
	while (line && ft_strncmp(line, delim, ft_strlen(line) + 1))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(fd);
	return (fd);
}
