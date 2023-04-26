/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:24:22 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 22:13:39 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	copystr(char *dest, char const *src, int i)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	res = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (0);
	i = copystr(res, s1, 0);
	i = copystr(res, s2, i);
	res[i] = 0;
	return (res);
}
