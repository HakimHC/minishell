/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:27:01 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/10 13:50:53 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *str)
{
	int		i;
	long	res;
	long	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10;
		res += str[i] - 48;
		i++;
	}
	if (str[i])
		return (0);
	return (res * sign);
}
