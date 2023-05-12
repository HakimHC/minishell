/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:44:16 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/12 12:45:11 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "minishell.h"

void	go_home(void)
{
	char	*home;

	home = ft_getenv("HOME");
	if (!home)
		return (ft_putendl_fd("cd: HOME not set", 2));
	chdir(home);
}

void	ft_cd(t_list *args)
{
	if (!args)
		return (go_home());
	if (ft_lstsize(args) > 1)
		return (ft_putstr_fd("cd: too many arguments\n", 2));
	if (args && chdir(args->content) == -1)
		perror(args->content);
}
