/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 03:18:01 by hakahmed          #+#    #+#             */
/*   Updated: 2023/03/23 13:12:54 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>

int	ft_printf(char const *s, ...);
int	ft_putstr(char *str);
int	ft_putchar(char c);
int	ft_putnbr(long n, int *len);
int	ft_putnbr_u(unsigned long int n, char c, int *len);
int	ft_putnbr_base(unsigned long int n, char *base, int *len);

#endif
