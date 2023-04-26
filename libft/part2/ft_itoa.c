/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:34:25 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/08 22:22:22 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_intlen(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		counter++;
		n = n / 10;
	}
	return (counter);
}

char	*helper(void)
{
	char	*int_min;
	int		i;
	char	*ptr;

	int_min = "-2147483648";
	ptr = (char *) malloc(12 * sizeof(char));
	if (!ptr)
		return (0);
	i = 0;
	while (int_min[i])
	{
		ptr[i] = int_min[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_negative_itoa(int n)
{
	int		len;
	char	*res;
	int		i;

	if (n == -2147483648)
		return (helper());
	n = -n;
	len = ft_intlen(n);
	res = (char *) malloc((len + 2) * sizeof(char));
	if (!res)
		return (0);
	res[0] = '-';
	i = len;
	while (i > 0)
	{
		res[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	res[len + 1] = 0;
	return (res);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;
	int		i;

	if (n < 0)
		return (ft_negative_itoa(n));
	len = ft_intlen(n);
	res = (char *) malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	i = len - 1;
	while (i >= 0)
	{
		res[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	res[len] = 0;
	return (res);
}
