/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:15:28 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 22:15:49 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				len;
	char			*ptr;

	i = 0;
	len = ft_strlen(s);
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
