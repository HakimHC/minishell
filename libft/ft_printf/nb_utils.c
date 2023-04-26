/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 03:21:41 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/13 14:55:55 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <limits.h>

int	ft_hexlen(unsigned long int n)
{
	int	counter;

	counter = 0;
	while (n)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

int	ft_putnbr_base(unsigned long int n, char *base, int *len)
{
	unsigned int					base_len;
	unsigned long					num;	

	num = n;
	if (n == ULONG_MAX)
		return (ft_putstr("ffffffffffffffff"));
	base_len = ft_strlen(base);
	if (num >= base_len)
	{
		ft_putnbr_base((num / base_len), base, len);
		ft_putnbr_base((num % base_len), base, len);
		return (0);
	}
	*len += write(1, (base + num), 1);
	return (0);
}

int	ft_pu(unsigned int n, int *len)
{
	if (n / 10 != 0)
		ft_pu(n / 10, len);
	*len += ft_putchar((n % 10) + 48);
	return (0);
}

int	ft_putnbr_u(unsigned long int n, char c, int *len)
{
	unsigned int	i;

	i = (unsigned int) n;
	if (c == 'x')
		return (ft_putnbr_base(n, "0123456789abcdef", len));
	if (c == 'X')
		return (ft_putnbr_base(n, "0123456789ABCDEF", len));
	if (c == 'p')
	{
		write(1, "0x", 2);
		*len += 2;
		return (ft_putnbr_base(n, "0123456789abcdef", len));
	}
	return (ft_pu(i, len));
}
