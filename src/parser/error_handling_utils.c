/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 04:02:22 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/22 21:31:57 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

unsigned char	is_redir(char *token)
{
	static char	*symb[] = {">", ">>", "<", "<<"};
	int			i;

	if (!token)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(token, symb[i], ft_strlen(symb[i])))
			return (1);
		i++;
	}
	return (0);
}

int	is_symb(char *token)
{
	return (is_redir(token) || !ft_strncmp(token, "|", 1));
}

int	print_token_error(char *token)
{
	ft_putstr_fd("fatal: ", 2);
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	g_data->exit_code = 2;
	return (1);
}
