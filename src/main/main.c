/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:03:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/03 22:48:40 by hakahmed         ###   ########.fr       */
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

t_list	*parse_envar(char *envar)
{
	t_env	*env;
	t_list	*node;
	int	i;
	int	j;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env || !ft_strchr(envar, '='))
		return (NULL);
	i = 0;
	j = 0;
	while (envar[j++] != '=');
	env->key = ft_substr(envar, i, j - 1);
	i += j;
	j = 0;
	while(envar[i + j])
		j++;
	env->value = ft_substr(envar, i, j);
	node = ft_lstnew(env);
	return (node);
}

t_list	*env_init(char *envp[])
{
	int	i;
	t_list	*head;
	t_list	*node;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		node = parse_envar(envp[i]);
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}

t_builtin	*populate_builtins(void)
{
	t_builtin	*res;

	res = malloc(sizeof(t_builtin));
	if (!res)
		return (NULL);
	res->cmd[0] = ft_strdup("env");
	res->f[0] = &ft_env;
	res->cmd[1] = ft_strdup("cd");
	res->f[1] = &ft_cd;
	res->cmd[2] = ft_strdup("export");
	res->f[2] = &ft_export;
	res->cmd[3] = ft_strdup("unset");
	res->f[3] = &ft_unset;
	res->cmd[4] = ft_strdup("pwd");
	res->f[4] = &ft_pwd;
	res->cmd[5] = ft_strdup("echo");
	res->f[5] = &ft_echo;
	res->cmd[6] = ft_strdup("exit");
	res->f[6] = &ft_exit;
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	/* atexit(leaks); */
	(void) argc;
	(void) argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->envp = env_init(envp);
	data->envparr = list_to_envars(data->envp);
	data->builtins = populate_builtins();
	if (!data->builtins)
		return (2);

	/* data->builtins->f[0](data->envp); */
	/* t_list *env = env_init(envp); */
	/* print_env(env); */
	/* data->stdin = dup(STDIN_FILENO); */
	/* ft_printf("%A", data->envp); */
	cmd_listen("$_ ");
	/* free(data->cmdtab->flags); */
	/* free(data->cmdtab); */
	/* free(data); */
	return (0);
}
