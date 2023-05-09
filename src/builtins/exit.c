/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:41:10 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/09 12:13:19 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

int	is_int(char *str)
{
	int	n;

	n = ft_atol(str);
	if ((n == 0) && (ft_strncmp(str, "0", 1)))
		return (0);
	return (1);
}

void	ft_exit(t_list *args)
{
	if (!args)
		exit(0);
	if (ft_lstsize(args) > 1)
		return (ft_putendl_fd("exit: too many arguments", 2));
	else if (!is_int(args->content))
	{
		ft_putendl_fd("exit: numerical value required", 2);
		exit(255);
	}
	exit(ft_atoi(args->content));
}
