/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 02:25:11 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 12:05:34 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
/*
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aux;
	t_list	*elem;
	t_list	*next;

	elem
	while (lst->next)
	{
		elem = ft_lstnew(f(lst->content));
		if (!elem)
		{
			del(elem->content);
			free(elem);
			return (0);
		}
		next = ft_lstnew(f(lst->next->content));
		if (!next)
		{
			del(next->content);
			free(next);
			return (0);
		}
		lst = lst->next;
		elem->next = next;
	}
	return (aux);
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;

	if (!lst)
		return (0);
	elem = ft_lstnew(f(lst->content));
	if (!elem)
	{
		del(elem->content);
		free(elem);
		elem = NULL;
		return (0);
	}
	elem->next = ft_lstmap(lst->next, f, del);
	return (elem);
}
