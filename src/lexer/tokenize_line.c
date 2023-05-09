/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:56:03 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/09 12:01:39 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

int	is_special_char(char c)
{
	return (!(!(ft_strchr("<>|", c))));
}

int	token_creator(t_list **head, char *line, int i)
{
	int		j;
	t_list	*token;

	j = 0;
	if (is_special_char(line[i]) && line[i])
	{
		while (is_special_char(line[i + j]) && line[i + j] != '|'
			&& line[i + j])
			j++;
		if (line[i + j] == '|')
			j++;
		token = ft_lstnew(ft_substr(line, i, j));
		ft_lstadd_back(head, token);
	}
	else if (line[i])
	{
		while (!is_special_char(line[i + j]) && !ft_isspace(line[i + j])
			&& line[i])
			j++;
		token = ft_lstnew(ft_substr(line, i, j));
		ft_lstadd_back(head, token);
	}
	return (j);
}

t_list	*split_line(char *line)
{
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		i += token_creator(&head, line, i);
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
	data->tokens = split_line(input);
	return (input_syntax_errors());
}
