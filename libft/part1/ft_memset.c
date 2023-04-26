/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:20:58 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/07 17:35:41 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char			*s;
	unsigned int	j;

	s = b;
	j = 0;
	while (j < len)
		s[j++] = c;
	return (b);
}
