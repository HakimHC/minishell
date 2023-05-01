/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:14:34 by hakim             #+#    #+#             */
/*   Updated: 2023/05/01 22:44:45 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

void	ft_unsetenv(char *var)
{
	t_list	*lst;
	t_list	*curr;
	t_list	*prev;

	lst = envars_to_list(data->envp);
	var = ft_strjoin(var, "=");
	curr = lst;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->content, var, ft_strlen(var)))
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
	free(var);
	data->envp = list_to_envars(lst);
	ft_printf("%A", data->envp);
}

void	ft_unset(t_list *args)
{
	t_list *curr;

	curr = args;
	while (curr)
	{
		ft_unsetenv(curr->content);
		curr = curr->next;
	}
}
