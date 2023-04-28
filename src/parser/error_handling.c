/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:23:57 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/28 04:35:46 by hakahmed         ###   ########.fr       */
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
		ft_putstr_fd("fatal: ", 2);
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		exit(258);
	}
	if (!curr)
		return ;
	while (curr->next)
		curr = curr->next;
	if (!ft_strncmp(curr->content, "|", 1))
	{
		ft_putstr_fd("fatal: ", 2);
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		exit(258);
	}
}

void	redir_parse_error(void)
{
	t_list	*curr;

	curr = data->tokens;
	while (curr)
	{
		if (is_redir(curr->content) && is_redir(curr->next->content))
			print_token_error(curr->next->content);
		else if (is_redir(curr->content) && ft_strlen(curr->content) > 2)
			print_token_error(curr->content);
		curr = curr->next;
	}
}
