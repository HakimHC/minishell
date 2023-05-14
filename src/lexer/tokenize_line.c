/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:56:03 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/14 19:33:23 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

int	is_special_char(char c)
{
	return (!(!(ft_strchr("<>|\'\"", c))));
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

void	expand(t_list *token)
{
	t_list *tmp;
	char *content;

	tmp = NULL;
	if (!ft_strchr(token->content, '$'))
		return ;
	content = token->content;
	int i = 0;
	int j;
	t_list *node;
	while (content[i])
	{
		j = 0;
		if (content[i] == '$')
		{
			i++;
			while (content[i + j] && content[i + j] != '$'
				&& !ft_isspace(content[i + j]))
				j++;
			node = ft_lstnew(ft_substr(content, i - 1, j + 1));
			/* ft_printf("{%s}\n", node->content); */
			ft_lstadd_back(&tmp, node);
			i += j;
		}
		else
		{
			while (content[i + j] && content[i + j] != '$')
				j++;
			node = ft_lstnew(ft_substr(content, i, j));
			/* ft_printf("{%s}\n", node->content); */
			ft_lstadd_back(&tmp, node);
			i += j;
		}
	}
	t_list *curr = tmp;
	while (curr)
	{
		if (ft_strchr(curr->content, '$') && ft_strncmp(curr->content, "$", 2))
		{
			char *aux = curr->content;
			if (ft_getenv(curr->content + 1))
				curr->content = ft_strdup(ft_getenv(curr->content + 1));
			else if (!ft_strncmp(curr->content, "$?", 3))
				curr->content = ft_itoa(data->exit_code);
			else
				curr->content = NULL;
			free(aux);
		}
		curr = curr->next;
	}
	char *res = ft_strdup("");
	curr = tmp;
	while (curr)
	{
		char *aux = res;
		if (curr->content)
			res = ft_strjoin(res, curr->content);
		else
			res = ft_strjoin(res, "");
		free(aux);
		curr = curr->next;
	}
	token->content = res;
	free(content);
	ft_lstclear(&tmp, free);
}

t_list *tokenize(char *input)
{
	t_list *node;
	t_list *head;

	int i = 0;
	int j;
	head = NULL;
	while (input[i])
	{
		if (!is_special_char(input[i]))
		{
			j = 0;
			while (input[i] && ft_isspace(input[i]))
				i++;
			while (input[i + j] && !is_special_char(input[i + j])
					&& !ft_isspace(input[i + j]))
				j++;
			//expand.....
			//
			node = ft_lstnew(ft_substr(input, i, j));
			expand(node);
			ft_lstadd_back(&head, node);
			/* ft_printf("[%s]\n", node->content); */
			i += j;
		}
		else if (input[i] != '\"' && input[i] != '\'' && is_special_char(input[i]))
		{
			char c = input[i];
			j = 0;
			while (input[i + j] && input[i + j] == c)
				j++;
			node = ft_lstnew(ft_substr(input, i, j));
			ft_lstadd_back(&head, node);
			/* ft_printf("[%s]\n", node->content); */
			i += j;
		}
		else if (input[i] == '\"' || input[i] == '\'')
		{
			char c = input[i++];
			j = 0;
			while (input[i + j] && input[i + j] != c)
				j++;
			node = ft_lstnew(ft_substr(input, i, j));
			if (c == 34)
				expand(node);
			ft_lstadd_back(&head, node);
			i += j;
			/* ft_printf("[%s]\n", node->content); */
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
	/* data->tokens = split_line(input); */
	data->tokens = tokenize(input);
	if (pre_token_parse_error(input))
	{
		print_token_error("|");
		return (1);
	}
	return (input_syntax_errors());
}
