/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:09:18 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/11 19:05:56 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	is_special_char(char c)
{
	return (!(!(ft_strchr("<>|\'\"", c))));
}

int	is_quote(char c)
{
	return (!(!(ft_strchr("\'\"", c))));
}

void	print_tokens()
{
	t_list	*curr;
	t_token	*token;

	curr = g_data->tokens;
	while (curr)
	{
		token = curr->content;
		printf("[%s]: %d\n", token->content, token->type);
		curr = curr->next;
	}
}
