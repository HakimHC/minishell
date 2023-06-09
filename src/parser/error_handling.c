/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:23:57 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/23 14:09:40 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

int	pipe_parse_error(void)
{
	t_list	*curr;
	t_token	*tkn;

	curr = g_data->tokens;
	tkn = curr->content;
	if (curr && tkn->content && ((char *)(tkn->content))[0] == '|')
		return (print_token_error("|"), 1);
	if (!curr)
		return (0);
	while (curr->next)
	{
		tkn = curr->content;
		if (tkn->content[0] == '|'
			&& ((t_token *)(curr->next->content))->content[0] == '|')
			return (print_token_error("|"), 1);
		curr = curr->next;
	}
	tkn = curr->content;
	if (!ft_strncmp(tkn->content, "|", 2))
		return (print_token_error("|"), 1);
	return (0);
}

int	redir_parse_error(void)
{
	t_list	*curr;
	t_token	*tkn;

	curr = g_data->tokens;
	while (curr)
	{
		tkn = curr->content;
		if (is_redir(tkn->content) && tkn->type == SYMB
			&& curr->next
			&& is_symb(((t_token *)curr->next->content)->content))
			return (print_token_error(tkn->content));
		else if (is_redir(tkn->content)
			&& ft_strlen(tkn->content) > 2 && tkn->type == SYMB)
			return (print_token_error(tkn->content));
		else if (!curr->next && is_redir(tkn->content) && tkn->type == SYMB)
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

int	parsing_errors(void)
{
	t_list	*curr;
	t_token	*tkn;
	t_token	*aux;

	curr = g_data->tokens;
	tkn = curr->content;
	if (is_symb(tkn->content) && !curr->next && tkn->type == SYMB)
		return (print_token_error(tkn->content));
	if (!ft_strncmp(tkn->content, "|", 2) && tkn->type == SYMB)
		return (print_token_error(tkn->content));
	while (curr && curr->next)
	{
		tkn = curr->content;
		aux = curr->next->content;
		if (is_symb(tkn->content) && is_symb(aux->content)
			&& tkn->type == SYMB && aux->type == SYMB)
		{
			if (!ft_strncmp(tkn->content, "|", 2)
				&& !ft_strncmp(aux->content, "<<", 3))
				;
			else
				return (print_token_error(aux->content));
		}
		curr = curr->next;
	}
	tkn = curr->content;
	if (is_symb(tkn->content) && tkn->type == SYMB)
			return (print_token_error(tkn->content));
	return (0);
}
