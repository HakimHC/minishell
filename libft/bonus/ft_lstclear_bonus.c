/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:28:44 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/29 02:52:31 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
/*
void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*curr;
	t_list	*temp;

	curr = *lst;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		del(temp->content);
		free(temp);
		temp = NULL;
	}
}
*/
void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	if (!*lst)
		return ;
	ft_lstclear(&(*lst)->next, del);
	del((*lst)->content);
	free(*lst);
	*lst = NULL;
}
