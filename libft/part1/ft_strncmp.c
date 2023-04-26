/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:06:05 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 12:05:31 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				diff;

	if (!n)
		return (0);
	i = 0;
	while (i < n)
	{
		diff = (unsigned char) s1[i] - (unsigned char) s2[i];
		if (diff || !(s1[i] && s2[i]))
		{
			return (diff);
		}
		i++;
	}
	return (diff);
}
