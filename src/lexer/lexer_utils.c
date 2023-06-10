/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:09:18 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/10 21:09:56 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	return (!(!(ft_strchr("<>|\'\"", c))));
}

int	is_quote(char c)
{
	return (!(!(ft_strchr("\'\"", c))));
}
