/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:09:47 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/09 02:07:42 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*d;
	const char		*s;
	char			temp[1997];

	i = 0;
	s = src;
	d = dst;
	if (!d && !s)
		return (0);
	while (i < len)
	{
		temp[i] = s[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		d[i] = temp[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
	char *a = malloc(5);
	char *b = malloc(5);

	a = "hola";
	b = "cola";

	b = (char *) ft_memcpy((char *) a, (char *) b, 4);
}*/
