/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:29:33 by hakim             #+#    #+#             */
/*   Updated: 2023/06/11 04:38:03 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

void	ft_env(t_list *args)
{
	t_list	*curr;
	t_env	*env;

	if (args)
	{
		printf("env: too many arguments\n");
		return ;
	}
	curr = g_data->envp;
	while (curr)
	{
		env = (t_env *) curr->content;
		printf("%s=%s\n", env->key, env->value);
		curr = curr->next;
	}
}
