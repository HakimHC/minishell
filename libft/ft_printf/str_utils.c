/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 03:06:11 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/10 12:09:00 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(long n, int *len)
{
	if (n < 0)
	{
		n = -n;
		*len += ft_putchar('-');
	}
	if (n / 10 != 0)
		ft_putnbr(n / 10, len);
	*len += ft_putchar((n % 10) + 48);
	return (0);
}
