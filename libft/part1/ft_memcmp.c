/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:21:19 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/09 02:07:08 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int			i;
	unsigned const char		*s1a;
	unsigned const char		*s2a;

	if (n)
	{
		i = 0;
		s1a = (unsigned const char *) s1;
		s2a = (unsigned const char *) s2;
		while (i < n)
		{
			if (s1a[i] - s2a[i])
				return ((s1a[i] - s2a[i]) + (s1a[i + 1] - s2a[i + 1]));
			i++;
		}
		return (0);
	}
	return (0);
}*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int			i;
	unsigned const char		*s1a;
	unsigned const char		*s2a;
	unsigned int			res;

	if (n)
	{
		i = 0;
		res = 0;
		s1a = (unsigned const char *) s1;
		s2a = (unsigned const char *) s2;
		while (i < n)
		{
			res += s1a[i] - s2a[i];
			if (s1a[i] - s2a[i])
				return (res);
			i++;
		}
		return (0);
	}
	return (0);
}
