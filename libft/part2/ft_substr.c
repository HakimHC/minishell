/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:59:59 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 13:47:08 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*ptr;

	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s) + 1;
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (0);
	i = 0;
	while (i < len && s[start])
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = 0;
	return (ptr);
}
