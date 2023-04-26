/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:11:32 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 13:42:42 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*k;
	unsigned int	i;

	if (!c && !n)
		return (0);
	k = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (k[i] == (unsigned char) c)
			return ((void *) s + i);
		i++;
	}
	if (!c)
		return ((void *) s + i);
	return (0);
}
