/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:03:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/27 15:35:25 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

t_data	*data;

void	check_flags(void)
{
	data->cmdtab = cmdtab_init();
	data->cmdtab->flags = set_flags(data);

	if ((*(data->cmdtab->flags) & HEREDOC) != 0)
		printf("HEREDOC ENABLED\n");
	if ((*(data->cmdtab->flags) & APPEND) != 0)
		printf("APPEND ENABLED\n");
	if ((*(data->cmdtab->flags) & REDIR_IN) != 0)
		printf("REDIR_IN ENABLED\n");
	if ((*(data->cmdtab->flags) & REDIR_OUT) != 0)
		printf("REDIR_OUT ENABLED\n");
}

void	leaks(void)
{
	system("leaks -q minishell");
}

void	print_cmdtab(void)
{
	printf("COMMAND: %s\n", data->cmdtab->cmd);
	ft_putstr("ARGS: ");
	print_list(data->cmdtab->args,0);
	ft_putstr("REDIR IN: ");
	print_list(data->cmdtab->redir_in, 0);
	ft_putstr("REDIR OUT: ");
	print_list(data->cmdtab->redir_out, 0);
	ft_putchar('\n');
}

int	main(void)
{
	atexit(leaks);
	char	*line;
	data = malloc(sizeof(t_data));
	if (!data)
		exit(69);
	line = readline("minishell$ ");
	while (ft_strncmp(line, "exit", 4))
	{
		printf("Line read: %s\n", line);
		add_history(line);
		t_list *tokens = split_line(line);
		data->tokens = tokens;
		check_flags();
		populate(data);
		print_cmdtab();
		free(line);
		line = readline("minishell$ ");
	}
	free(line);
	free(data->cmdtab->flags);
	ft_lstclear(&(data->tokens), &free);
	free(data->cmdtab);
	free(data);
	return (0);
}
