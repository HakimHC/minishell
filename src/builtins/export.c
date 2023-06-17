/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:30:22 by hakim             #+#    #+#             */
/*   Updated: 2023/06/16 23:13:50 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

void	export_noargs(void)
{
	t_list	*curr;
	t_env	*env;

	curr = g_data->envp;
	while (curr)
	{
		env = curr->content;
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		curr = curr->next;
	}
}

void	ft_export(t_list *args)
{
	t_list	*curr;
	char	*aux;

	curr = args;
	if (!curr)
		return ((void) export_noargs());
	while (curr)
	{
		if (!export_error(curr->content))
		{
			if (curr->next)
			{
				aux = ft_strjoin(curr->content, curr->next->content);
				curr = curr->next;
			}
			else
			 	aux = ft_strdup(curr->content);
			ft_setenv(aux);
			free(aux);
		}
		if (curr)
			curr = curr->next;
	}
	ft_free_strarr(g_data->envparr);
	g_data->envparr = list_to_envars(g_data->envp);
}
