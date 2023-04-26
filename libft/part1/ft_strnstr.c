/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:54:30 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 22:18:44 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int		i;
	unsigned int		j;

	i = 0;
	if (ft_strlen(needle) < 1)
		return ((char *) haystack);
	j = 0;
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j] && needle[j] && (i + j) < len)
			j++;
		if (!(needle[j]))
			return ((char *) haystack + i);
		i++;
		j = 0;
	}
	return (0);
}
