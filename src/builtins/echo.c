/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:33:45 by hakim             #+#    #+#             */
/*   Updated: 2023/05/01 17:39:07 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_echo(t_list	*args)
{
	t_list	*curr;

	curr = args;
	while (curr)
	{
		write(STDOUT_FILENO, curr->content, ft_strlen(curr->content));
		if (curr->next)
			write(STDOUT_FILENO, " ", 1);
		curr = curr->next;
	}
	if (ft_strncmp(curr->content, "-n", 2))
		write(STDOUT_FILENO, "\n", 1);
}
