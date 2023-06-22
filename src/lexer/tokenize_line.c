/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:56:03 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/22 01:05:44 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

t_list	*tokenize(char *input)
{
	t_list	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (!is_special_char(input[i]))
			i = mk_normal(input, i, &head);
		else if (!is_quote(input[i]) && is_special_char(input[i]))
			i = mk_symbol(input, i, &head);
		else if (is_quote(input[i]))
		{
			i = mk_quote(input, i, &head);
			if (!input[i])
				return (head);
			i++;
		}
		while (input[i] && ft_isspace(input[i]))
			i++;
	}
	return (head);
}

int	input_syntax_errors(void)
{
	if (pipe_parse_error() || redir_parse_error())
		return (1);
	return (0);
}

int	tokenize_input(char *input)
{
	g_data->tokens = tokenize(input);
	/* print_tokens(); */
	return (parsing_errors());
}
