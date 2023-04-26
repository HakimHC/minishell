/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:46:04 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/13 20:38:05 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_seplen(char const *str, char sep, int i)
{
	int	len;

	len = 0;
	while (str[i] != sep && str[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	count_words(char const *str, char sep)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	if (!str[0])
		return (0);
	if (str[0] != sep)
		counter++;
	while (str[i + 1])
	{
		if (str[i] == sep && str[i + 1] != sep)
			counter++;
		i++;
	}
	return (counter);
}

char	*fill_arr(char const *str, int j, int len)
{
	char	*out;
	int		i;

	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (0);
	i = 0;
	while (i < len)
	{
		out[i] = str[j];
		i++;
		j++;
	}
	out[i] = 0;
	return (out);
}

void	free_arr(char *arr[])
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		arr_len;
	char	**arr;
	int		i;
	int		j;

	arr_len = count_words(s, c);
	arr = (char **) malloc((arr_len + 1) * sizeof(char *));
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (i < arr_len)
	{
		while (s[j] == c)
			j++;
		arr[i] = fill_arr(s, j, ft_seplen(s, c, j));
		if (!arr[i])
			return (free_arr(arr), NULL);
		j += ft_seplen(s, c, j);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
//
// int	main(int argc, char **argv)
// {
// 	char	**out = ft_split(argv[1], argv[2][0]);
// 	int	i = 0;
// 	while (out[i])
// 	{
// 		printf("%s\n", out[i]);
// 		i++;
// 	}
// }
