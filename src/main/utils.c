/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:08:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/22 23:47:50 by hakahmed         ###   ########.fr       */
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

char	*tstline(void)
{
	char *aux;
	char *line;

	line = get_next_line(0);
	if (!line)
		return NULL;
	aux = line;
	line = ft_substr(line, 0, ft_strlen(line) - 1);
	free(aux);
	return (line);
}

void	cmd_listen(char *prompt)
{
	char	*line;

	/* line = readline(prompt); */
	(void) prompt;
	line = tstline();
	while (line)
	{
		sighandler();
		if (!empty_line(line))
		{
			/* add_history(line); */
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
		g_data->sig_hd = 0;
		line = "";
		/* line = readline(prompt); */
		line = tstline();
	}
	free(line);
	exit(g_data->exit_code);
}
