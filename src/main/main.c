/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:03:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/15 10:30:22 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

t_data	*data;

t_list	*parse_envar(char *envar)
{
	t_env	*env;
	t_list	*node;
	int		i;
	int		j;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env || !ft_strchr(envar, '='))
		return (NULL);
	i = 0;
	j = 0;
	while (envar[j++] != '=')
		;
	env->key = ft_substr(envar, i, j - 1);
	i += j;
	j = 0;
	while (envar[i + j])
		j++;
	env->value = ft_substr(envar, i, j);
	node = ft_lstnew(env);
	return (node);
}

t_list	*env_init(char *envp[])
{
	int		i;
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

void	db(char *line)
{

	if (pre_token_parse_error(line))
	{
		print_token_error("|");
		exit(1);
	}
	if (!tokenize_input(line))
	{
		fill_cmdtab();
		/* print_cmdtab(); */
		executor(data->cmdtab);
	}
}

int	main(int argc, char **argv, char **envp)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->envp = env_init(envp);
	data->envparr = list_to_envars(data->envp);
	data->builtins = populate_builtins();
	if (!data->builtins)
		return (2);
	if (argc == 2)
		db(argv[1]);
	else
		cmd_listen("\033[6;35;1mminishell$\033[0m ");
	return (0);
}
