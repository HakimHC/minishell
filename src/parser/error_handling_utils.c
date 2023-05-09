/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 04:02:22 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/09 11:44:25 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

unsigned char	is_redir(char *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token, ">", 1))
		return (1);
	if (!ft_strncmp(token, "<", 1))
		return (1);
	if (!ft_strncmp(token, ">>", 2))
		return (2);
	if (!ft_strncmp(token, "<<", 2))
		return (1);
	return (0);
}

int	print_token_error(char *token)
{
	ft_putstr_fd("fatal: ", 2);
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}
