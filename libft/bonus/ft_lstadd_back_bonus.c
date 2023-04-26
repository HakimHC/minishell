/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:57:35 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/30 20:43:49 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*curr;

	curr = *lst;
	if (!*lst)
		*lst = new_node;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}
