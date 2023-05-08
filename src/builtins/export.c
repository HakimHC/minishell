/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:30:22 by hakim             #+#    #+#             */
/*   Updated: 2023/05/04 02:30:14 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

void	ft_export(t_list *args)
{
	t_list	*curr;

	curr = args;
	while (curr)
	{
		if (!export_error(curr->content))
			ft_setenv(curr->content);
		curr = curr->next;
	}
	ft_free_strarr(data->envparr);
	data->envparr = list_to_envars(data->envp);
}
