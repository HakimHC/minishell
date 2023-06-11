/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:33:45 by hakim             #+#    #+#             */
/*   Updated: 2023/06/11 04:42:51 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_echo(t_list	*args)
{
	t_list			*curr;
	unsigned char	n;

	curr = args;
	n = 0;
	if (!args)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (!ft_strncmp(curr->content, "-n", 3))
	{
		n = 1;
		curr = curr->next;
	}
	while (curr)
	{
		write(STDOUT_FILENO, curr->content, ft_strlen(curr->content));
		if (*(char *)curr->content && curr->next
			&& *(char *)curr->next->content)
			write(STDOUT_FILENO, " ", 1);
		curr = curr->next;
	}
	if (!n)
		write(STDOUT_FILENO, "\n", 1);
}
