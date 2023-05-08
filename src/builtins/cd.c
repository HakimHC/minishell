/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:44:16 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/03 18:21:34 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

void	ft_cd(t_list *args)
{
	if (ft_lstsize(args) > 1)
		return (ft_putstr_fd("cd: too many arguments\n", 2));
	if (args && chdir(args->content) == -1)
		perror(args->content);
}
