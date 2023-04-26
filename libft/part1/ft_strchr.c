/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:44:28 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/10 14:04:07 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*d;
	int		i;

	if (!s)
		return (0);
	d = (char *) s;
	i = 0;
	while (d[i])
	{
		if (d[i] == (unsigned char) c)
			return (d + i);
		i++;
	}
	if (c == '\0')
		return (d + i);
	return (0);
}
