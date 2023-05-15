/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:56:03 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/15 15:58:36 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

int	is_special_char(char c)
{
	return (!(!(ft_strchr("<>|\'\"", c))));
}

int	is_quote(char c)
{
	return (!(!(ft_strchr("\'\"", c))));
}

char *expand(char *token)
{
	t_list *tmp;
	char *content;

	tmp = NULL;
	if (!ft_strchr(token, '$'))
		return (token);
	content = token;
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
	free(content);
	ft_lstclear(&tmp, free);
	return (res);
}

t_list *mk_tkn(char *input, int type)
{
	t_token	*tkn;
	t_list	*node;

	tkn = (t_token *) malloc(sizeof(t_token));
	if (!tkn)
		perror_exit("malloc");
	tkn->content = input;
	tkn->type = type;
	node = ft_lstnew(tkn);
	return (node);
}

int	mk_normal(char *input, int i, t_list **head)
{
	int	j;
	t_list	*node;
	char	*exp;

	j = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	while (input[i + j] && !is_special_char(input[i + j])
			&& !ft_isspace(input[i + j]))
		j++;
	node = mk_tkn(ft_substr(input, i, j), NORM);
	exp = expand(((t_token *)node->content)->content);
	((t_token *)node->content)->content = exp;
	ft_lstadd_back(head, node);
	i += j;
	return (i);
}

int	mk_symbol(char *input, int i, t_list **head)
{
	int	j;
	char	c;
	t_list	*node;
	char	*exp;

	c = input[i];
	j = 0;
	while (input[i + j] && input[i + j] == c)
		j++;
	node = mk_tkn(ft_substr(input, i, j), SYMB);
	exp = expand(((t_token *)node->content)->content);
	((t_token *)node->content)->content = exp;
	ft_lstadd_back(head, node);
	i += j;
	return (i);
}

int	concat_tkn(char *input, int i, t_list *tkn)
{
	char	c;
	int	j;
	char	*content;
	char	*tmp;
	t_token	*cn;

	c = input[i++];
	j = 0;
	while (input[i + j] && input[i + j] != c)
		j++;
	if (c == 34)
		content = expand(ft_substr(input, i, j));
	else
		content = ft_substr(input, i, j);
	cn = tkn->content;
	tmp = cn->content;
	cn->content = ft_strjoin(cn->content, content);
	free(tmp);
	return (i);
}

int	mk_quote(char *input, int i, t_list **head)
{
	char	c;
	int	j;
	t_list	*node;
	char	*exp;

	c = input[i++];
	j = 0;
	while (input[i + j] && input[i + j] != c)
		j++;
	node = mk_tkn(ft_substr(input, i, j), NORM);
	if (c == 34)
	{
		exp = expand(((t_token *)node->content)->content);
		((t_token *)node->content)->content = exp;
	}
	i += j + 1;
	/* t_token *tkn = node->content; */
	/* printf("[%s]\n", tkn->content); */
	/* while (is_quote(input[i])) */
	/* 	i = concat_tkn(input, i, node) + 1; */
	i--;
	ft_lstadd_back(head, node);
	return (i);
}

t_list *tokenize(char *input)
{
	t_list *head;
	int	i;

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
	data->tokens = tokenize(input);
	if (pre_token_parse_error(input))
	{
		print_token_error("|");
		return (1);
	}
	return (input_syntax_errors());
}
