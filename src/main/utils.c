/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:08:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/15 10:41:33 by hakahmed         ###   ########.fr       */
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
		return true;
	return false;
}

void	leaks(void)
{
	system("leaks -q minishell");
}

void	cmd_listen(char *prompt)
{
	char	*line;

	line = readline(prompt);
	while (1)
	{
		if (!empty_line(line))
		{
			add_history(line);
			if (!tokenize_input(line))
			{
				fill_cmdtab();
				/* print_cmdtab(); */
				executor(data->cmdtab);
				destroyer();
			}
			else
				ft_lstclear(&(data->tokens), free); 
		}
		free(line);
		/* system("leaks -q minishell"); */
		line = readline(prompt);
	}
	free(line);
}

void	free_redirs(t_list *redirs)
{
	t_redir	*curr;

	while (redirs)
	{
		curr = redirs->content;
		free(curr->file);
		redirs = redirs->next;
	}
}

void	free_cmdtab()
{
	t_cmdtab 	*curr;
	t_cmdtab	*aux;

	curr = data->cmdtab;
	while (curr)
	{
		aux = curr;
		free(curr->cmd);
		ft_lstclear(&(curr->args), &free);
		free_redirs(curr->redir_in);
		free_redirs(curr->redir_out);
		ft_lstclear(&(curr->redir_in), &free);
		ft_lstclear(&(curr->redir_out), &free);
		curr = curr->next;
		free(aux);
	}
	data->cmdtab = NULL;
}

void	destroyer(void)
{
	free_cmdtab();
	ft_lstclear(&(data->tokens), &free);
}
