/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:09:18 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/20 11:15:51 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	is_special_char(char c)
{
	return (!(!(ft_strchr("<>|\'\"", c))));
}

int	is_quote(char c)
{
	return (!(!(ft_strchr("\'\"", c))));
}

void	print_tokens(void)
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

int	cncat_util(char *input, int i, t_list *tkn)
{
	int		j;
	char	*content;
	t_token	*cn;
	char	*tmp;

	j = 0;
	while (input[i + j] && !is_special_char(input[i + j])
		&& !ft_isspace(input[i + j]))
		j++;
	cn = tkn->content;
	tmp = cn->content;
	content = ft_substr(input, i, j);
	cn->content = ft_strjoin(cn->content, content);
	free(content);
	free(tmp);
	return (i + j - 1);
}
