/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 02:58:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/26 19:23:13 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include "ft_printf.h"
#include "libft.h"

int	ft_arr_h(char **arr, char flag)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (arr[i])
	{
		len += ft_putstr(arr[i]);
		if (flag == 'a')
			ft_putchar(' ');
		else
			ft_putchar('\n');
		i++;
		len++;
	}
	if (flag == 'a')
		ft_putchar(' ');
	else
		ft_putchar('\n');
	return (len + 1);
}

int	flag_check(char flag, va_list args, int *len)
{
	if (flag == 'a' || flag == 'A')
		return (ft_arr_h(va_arg(args, char **), flag));
	if (flag == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (flag == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (flag == 'i' || flag == 'd')
		return (ft_putnbr(va_arg(args, int), len));
	if (flag == 'x' || flag == 'X' || flag == 'u')
		return (ft_putnbr_u(va_arg(args, unsigned int ), flag, len));
	if (flag == '%')
		return (ft_putchar('%'));
	if (flag == 'p')
		return (ft_putnbr_u(va_arg(args, unsigned long int), flag, len));
	return (0);
}

int	ft_printf(char const *s, ...)
{
	int		i;
	va_list	args;
	int		len;

	i = 0;
	len = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			len += flag_check(s[i + 1], args, &len);
			i += 2;
		}
		else
		{
			write(1, (s + i), 1);
			len++;
			i++;
		}
	}
	va_end(args);
	return (len);
}
