/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:30:22 by hakim             #+#    #+#             */
/*   Updated: 2023/06/23 05:00:35 by hakahmed         ###   ########.fr       */
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

	curr = args;
	if (!curr)
		return ((void) export_noargs());
	while (curr)
	{
		if (!export_error(curr->content))
		{
			g_data->exit_code = 0;
			ft_setenv(curr->content);
		}
		if (curr)
			curr = curr->next;
	}
	ft_free_strarr(g_data->envparr);
	g_data->envparr = list_to_envars(g_data->envp);
}
