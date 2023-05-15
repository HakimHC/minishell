/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:23:57 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/15 13:56:50 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "minishell.h"

int	pipe_parse_error(void)
{
	t_list	*curr;
	t_token	*tkn;

	curr = data->tokens;
	tkn = curr->content;
	if (curr && tkn->content && ((char *)(tkn->content))[0] == '|')
	{
		ft_putstr_fd("fatal: ", 2);
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	if (!curr)
		return (0);
	while (curr->next)
		curr = curr->next;
	tkn = curr->content;
	if (!ft_strncmp(tkn->content, "|", 1))
	{
		ft_putstr_fd("fatal: ", 2);
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	return (0);
}

int	redir_parse_error(void)
{
	t_list	*curr;
	t_token	*tkn;

	curr = data->tokens;
	while (curr)
	{
		tkn = curr->content;
		if (is_redir(curr->content)
			&& curr->next
			&& is_redir(((t_token *)curr->next->content)->content))
			return (print_token_error(curr->content));
		else if (is_redir(tkn->content)
			&& ft_strlen(tkn->content) > 2)
			return (print_token_error(curr->content));
		else if (!curr->next && is_redir(tkn->content))
			return (print_token_error(tkn->content));
		curr = curr->next;
	}
	return (0);
}

char	*ft_strchrset(char *str, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j] && str[i] != set[j])
			j++;
		if (set[j])
		{
			while (str[i] == set[j])
				i++;
			return (str + i);
		}
		i++;
	}
	return (NULL);
}

int	pre_token_parse_error(char *input)
{
	int	i;

	input = ft_strchrset(input, "<>");
	while (input)
	{
		i = 0;
		if (input[i] == '|')
			return (0);
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '|')
			return (1);
		input = ft_strchrset(input, "<>");
	}
	return (0);
}
