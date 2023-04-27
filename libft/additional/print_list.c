/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 23:11:54 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/27 15:31:58 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_list(t_list *head, int  nl)
{
	if (!head)
		return ;
	if (nl)
		ft_printf("%s\n", (char *) head->content);
	else
		ft_printf("%s ", (char *) head->content);
	print_list(head->next, nl);
}
