/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:14:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/04 02:29:06 by hakahmed         ###   ########.fr       */
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
	int	i;

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

	curr = data->envp;
	while (curr)
	{
		env = curr->content;
		if (!ft_strncmp(env->key, arg, ft_strlen(env->key) + 1))
			return (env->value);
		curr = curr->next;
	}
	return (NULL);
}

unsigned char process_env(t_env *env)
{
	t_list	*curr;
	t_env	*curr_env;

	curr = data->envp;
	while (curr)
	{
		curr_env = curr->content;
		if (!ft_strcmp(curr_env->key, env->key) && ft_strcmp(curr_env->value, env->value))
		{
			free(curr_env->value);
			free(env->key);
			curr_env->value = ft_strdup(env->value);
			free(env);
			free(env->value);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	ft_setenv(char *arg)
{
	t_env	*env;
	int	i;
	int	j;
	t_list	*node;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env || !ft_strchr(arg, '='))
		return ;
	i = 0;
	j = 0;
	while (arg[j++] != '=');
	env->key = ft_substr(arg, i, j - 1);
	i += j;
	j = 0;
	while(arg[i + j])
		j++;
	env->value = ft_substr(arg, i, j);
	if (!process_env(env))
	{
		node = ft_lstnew(env);
		ft_lstadd_back(&(data->envp), node);
	}
}

unsigned char export_error(char *arg)
{
	int	i;

	i = -1;
	while (ft_isspace(arg[++i]));
	if (arg[i] == '=')
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}
