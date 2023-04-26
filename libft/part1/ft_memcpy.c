/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:09:47 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/09 01:17:31 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*d;
	const char		*s;

	i = 0;
	s = (const char *) src;
	d = (char *) dst;
	if (!s && !dst)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
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
