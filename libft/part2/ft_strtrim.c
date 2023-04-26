/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:13:13 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/07 21:47:45 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_issep(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_isend(char const *str, int i, char const *set)
{
	while (str[i])
	{
		if (!ft_issep(str[i], set))
			return (0);
		i++;
	}
	return (1);
}

int	ft_getlen(char const *str, int i, char const *set)
{
	int	len;

	len = 0;
	while (!ft_isend(str, i, set))
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	while (ft_issep(s1[i], set))
		i++;
	len = ft_getlen(s1, i, set);
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (0);
	j = 0;
	while (j < len)
		ptr[j++] = s1[i++];
	ptr[j] = 0;
	return (ptr);
}
/*
int	main(int argc, char **argv)
{
	printf("%s\n", ft_strtrim(argv[1], argv[2]));
}*/
