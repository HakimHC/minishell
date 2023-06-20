/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:08:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/21 00:33:02 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "libft.h"
#include "minishell.h"

bool	empty_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (true);
	return (false);
}

void	cmd_listen(char *prompt)
{
	char	*line;

	line = readline(prompt);
	while (line)
	{
		sighandler();
		if (!empty_line(line))
		{
			add_history(line);
			if (!tokenize_input(line))
			{
				fill_cmdtab();
				executor(g_data->cmdtab);
				destroyer();
			}
			else
				free_tokens();
		}
		free(line);
		line = readline(prompt);
	}
	free(line);
	exit(g_data->exit_code);
}
