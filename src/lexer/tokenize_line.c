/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:56:03 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/28 04:52:55 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

int	is_special_char(char c)
{
	return (!(!(ft_strchr("<>|", c))));
}

t_list	*split_line(char *line)
{
	t_list *head;
	t_list	*token;
	int	i;
	int	j;

	i = 0;
	head = NULL;
	while (line[i])
	{
		j = 0;
		while (ft_isspace(line[i]))
			i++;
		if (is_special_char(line[i]) && line[i])
		{
			while (is_special_char(line[i + j]) && line[i + j] != '|' && line[i + j])
				j++;
			if (line[i + j] == '|')
				j++;
			token = ft_lstnew(ft_substr(line, i, j));
			/* ft_printf("TOKEN [%s]\n", token->content); */
			ft_lstadd_back(&head, token);
		}
		else if (line[i])
		{
			while (!is_special_char(line[i + j]) && !ft_isspace(line[i + j]) && line[i])
				j++;
			token = ft_lstnew(ft_substr(line, i, j));
			/* ft_printf("TOKEN [%s]\n", token->content); */
			ft_lstadd_back(&head, token);
		}
		i += j;
	}
	/* print_list(head, 1); */
	return (head);
}

void	input_syntax_errors(void)
{
	pipe_parse_error();
	redir_parse_error();
}

void	tokenize_input(char *input)
{
	data->tokens = split_line(input);
	input_syntax_errors();
}

