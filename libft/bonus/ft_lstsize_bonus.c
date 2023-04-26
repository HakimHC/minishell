/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:43:54 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/07 20:47:24 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		counter;

	curr = lst;
	counter = 0;
	while (curr)
	{
		counter++;
		curr = curr->next;
	}
	return (counter);
}
