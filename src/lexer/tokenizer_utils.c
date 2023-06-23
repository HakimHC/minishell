/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:15:10 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/23 10:42:04 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

t_list	*mk_tkn(char *input, int type)
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
	int		j;
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
	i += j;
	while ((is_quote(input[i]) && input[i]) || (input[i]
			&& !ft_isspace(input[i]) && !is_special_char(input[i])))
	{
		if (exp[ft_strlen(exp) - 1] == '$')
		{
			free(exp);
			((t_token *)node->content)->content = ft_strdup("");
		}
		i = concat_tkn(input, i, node);
		i++;
	}
	ft_lstadd_back(head, node);
	return (i);
}

int	mk_symbol(char *input, int i, t_list **head)
{
	int		j;
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
	int		j;
	char	*content;
	char	*tmp;
	t_token	*cn;

	if (!is_special_char(input[i]))
		return (cncat_util(input, i, tkn));
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
	free(content);
	return (i + j);
}

int	mk_quote(char *input, int i, t_list **head)
{
	char	c;
	int		j;
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
	i += j;
	while ((is_quote(input[++i]) && input[i])
		|| (input[i] && !is_special_char(input[i])
			&& !ft_isspace(input[i])))
		i = concat_tkn(input, i, node);
	ft_lstadd_back(head, node);
	return (i - 1);
}
