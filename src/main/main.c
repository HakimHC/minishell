/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:03:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/28 04:48:07 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

t_data	*data;

void	leaks(void)
{
	system("leaks -q minishell");
}

int	main(void)
{
	/* atexit(leaks); */
	extern char **environ;
	data = malloc(sizeof(t_data));
	if (!data)
		exit(69);
	data->envp = environ;
	/* ft_printf("%A", data->envp); */
	cmd_listen("minishell$ ");
	/* free(data->cmdtab->flags); */
	/* free(data->cmdtab); */
	/* free(data); */
	return (0);
}
