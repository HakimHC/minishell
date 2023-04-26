/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:45:01 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 22:19:38 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	index;
	unsigned int	lensrc;
	unsigned int	lendest;

	i = 0;
	lensrc = ft_strlen(src);
	lendest = ft_strlen(dest);
	index = lendest;
	if (dstsize < lendest)
		return (dstsize + lensrc);
	if (dstsize > lendest)
	{
		while ((i < dstsize - lendest - 1) && src[i])
		{
			dest[index] = src[i];
			i++;
			index++;
		}
	}
	dest[index] = 0;
	return (lendest + lensrc);
}

/*int	main(void)
{
	char str1[15] = "Hakim";
	char str2[] = "Ahmed";
	char *final = ft_strncat(str1, str2, 3);
	printf("%s", final);
//	char *final = strcat(str1, str2);
//	printf("%s", final);
}*/
