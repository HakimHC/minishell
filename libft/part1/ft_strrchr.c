/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:44:28 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/09 01:00:12 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*d;
	int		i;

	d = (char *) s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (d[i] == (unsigned char) c)
			return (d + i);
		i--;
	}
	return (0);
}
