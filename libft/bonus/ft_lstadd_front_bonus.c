/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:23:23 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/30 20:44:09 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	t_list	*temp;

	if (*lst)
	{
		temp = *lst;
		*lst = new_node;
		new_node->next = temp;
	}
	else
		*lst = new_node;
}
