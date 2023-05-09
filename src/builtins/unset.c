/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:14:34 by hakim             #+#    #+#             */
/*   Updated: 2023/05/09 12:11:33 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

void	ft_unsetenv(char *var)
{
	t_list	*lst;
	t_list	*curr;
	t_list	*prev;
	t_env	*env;

	lst = data->envp;
	curr = data->envp;
	prev = NULL;
	while (curr)
	{
		env = curr->content;
		if (!ft_strncmp(env->key, var, ft_strlen(env->key) + 1))
		{
			if (prev)
				prev->next = curr->next;
			else
				lst = lst->next;
			ft_lstdelone(curr, &free);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(t_list *args)
{
	t_list	*curr;

	curr = args;
	while (curr)
	{
		ft_unsetenv(curr->content);
		curr = curr->next;
	}
	ft_free_strarr(data->envparr);
	data->envparr = list_to_envars(data->envp);
}
