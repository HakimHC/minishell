/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:23:57 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/27 18:34:32 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

void	pipe_parse_error(void)
{
	t_list	*curr;

	curr = data->tokens;
	if (curr && curr->content && ((char *)(curr->content))[0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		exit(258);
	}
}
