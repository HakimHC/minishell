/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:33:45 by hakim             #+#    #+#             */
/*   Updated: 2023/06/23 07:04:23 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

int	n_arg(char *arg)
{
	if (ft_strncmp(arg, "-n", 2))
		return (0);
	arg += 2;
	while (*arg && *arg == 'n')
		arg++;
	return (!*arg);
}

void	ft_echo(t_list	*args)
{
	t_list			*curr;
	unsigned char	n;

	curr = args;
	n = 0;
	if (!args)
		return ((void)write(STDOUT_FILENO, "\n", 1));
	if (n_arg(curr->content))
	{
		n = 1;
		curr = curr->next;
	}
	while (curr)
	{
		if (!n_arg(curr->content) ||  n == 0)
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
