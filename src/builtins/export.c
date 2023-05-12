/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:30:22 by hakim             #+#    #+#             */
/*   Updated: 2023/05/12 21:33:46 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

void	ft_export(t_list *args)
{
	// export doesnt work with quotes, sometimes it duplicates envars

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
