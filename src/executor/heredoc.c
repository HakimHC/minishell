/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:19:41 by hakim             #+#    #+#             */
/*   Updated: 2023/05/01 12:20:11 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>

#include "minishell.h"

int	handle_heredoc(char *delim)
{
	int	fd;
	char	*line;

	line = readline("heredoc> ");
	fd = ft_open("/tmp/.heredoc", O_CREAT | O_TRUNC | O_RDONLY);
	while (ft_strncmp(line, delim, ft_strlen(line)))
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	return (fd);
}

