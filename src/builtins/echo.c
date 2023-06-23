/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:33:45 by hakim             #+#    #+#             */
/*   Updated: 2023/06/23 00:10:51 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

void	ft_echo(t_list	*args)
{
	t_list			*curr;
	unsigned char	n;

	curr = args;
	n = 0;
	if (!args)
		return ((void)write(STDOUT_FILENO, "\n", 1));
	if (!ft_strncmp(curr->content, "-n", 3))
	{
		n = 1;
		curr = curr->next;
	}
	while (curr)
	{
		if (ft_strncmp(curr->content, "-n", 3) ||  n == 0)
		{
			write(STDOUT_FILENO, curr->content, ft_strlen(curr->content));
			if (curr->next)
				write(STDOUT_FILENO, " ", 1);
		}
		curr = curr->next;
	}
	if (!n)
		write(STDOUT_FILENO, "\n", 1);
}
