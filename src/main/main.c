/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:03:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/01 22:37:12 by hakim            ###   ########.fr       */
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

char	**ft_arrdup(char **arr)
{
	int	i;
	char	**res;

	i = 0;
	while (arr[i])
		i++;
	res = (char **) malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	/* atexit(leaks); */
	(void) argc;
	(void) argv;
	data = malloc(sizeof(t_data));
	if (!data)
		exit(69);
	data->envp = ft_arrdup(envp);
	/* data->stdin = dup(STDIN_FILENO); */
	/* ft_printf("%A", data->envp); */
	cmd_listen("$> ");
	/* free(data->cmdtab->flags); */
	/* free(data->cmdtab); */
	/* free(data); */
	return (0);
}
