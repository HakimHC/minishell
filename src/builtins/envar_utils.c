/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:14:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/23 05:23:44 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

char	**list_to_envars(t_list *head)
{
	char	**envars;
	t_list	*curr;
	t_env	*env;
	char	*aux;
	int		i;

	envars = (char **) malloc((ft_lstsize(head) + 1) * sizeof(char *));
	if (!envars)
		return (NULL);
	i = 0;
	curr = head;
	while (curr)
	{
		env = curr->content;
		aux = ft_strjoin(env->key, "=");
		envars[i] = ft_strjoin(aux, env->value);
		free(aux);
		i++;
		curr = curr->next;
	}
	envars[i] = NULL;
	return (envars);
}

char	*ft_getenv(char *arg)
{
	t_list	*curr;
	t_env	*env;

	curr = g_data->envp;
	while (curr)
	{
		env = curr->content;
		if (!ft_strncmp(env->key, arg, ft_strlen(env->key) + 1))
			return (env->value);
		curr = curr->next;
	}
	return (NULL);
}

unsigned char	process_env(t_env *env)
{
	t_list	*curr;
	t_env	*curr_env;

	curr = g_data->envp;
	while (curr)
	{
		curr_env = curr->content;
		if (!ft_strncmp(curr_env->key, env->key, ft_strlen(env->key) + 1))
		{
			free(curr_env->value);
			free(env->key);
			curr_env->value = ft_strdup(env->value);
			free(env->value);
			free(env);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	ft_setenv(char *arg)
{
	t_env	*env;
	int		i;
	int		j;
	t_list	*node;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env || !ft_strchr(arg, '='))
		return ;
	i = 0;
	j = 0;
	while (arg[j++] != '=')
		;
	env->key = ft_substr(arg, i, j - 1);
	i += j;
	j = 0;
	while (arg[i + j])
		j++;
	env->value = ft_substr(arg, i, j);
	if (!process_env(env))
	{
		node = ft_lstnew(env);
		ft_lstadd_back(&(g_data->envp), node);
	}
}

unsigned char	export_error(char *arg)
{
	int	i;

	i = -1;
	if (*arg == '?')
	{
		g_data->exit_code = EXIT_FAILURE;
		return (ft_putstr_fd("export: '?': not a valid identifier\n", 2), 1);
	}
	while (ft_isspace(arg[++i]))
		;
	if (arg[i] == '=')
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_data->exit_code = EXIT_FAILURE;
		return (1);
	}
	if (!ft_strchr(arg, '='))
		return (1);
	return (0);
}
