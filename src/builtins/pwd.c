/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:43:20 by hakim             #+#    #+#             */
/*   Updated: 2023/05/03 12:46:09 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

void	ft_pwd(t_list *args)
{
	char	*wd;
	size_t	size;

	if (ft_lstsize(args) > 0)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	size = 50;
	wd = (char *) malloc((size + 1)* sizeof(char));
	if (!wd)
		return ;
	while (1)
	{
		if (!getcwd(wd, size))
		{
			printf("size: %lu\n", size);
			size += 10;
			free(wd);
			wd = (char *) malloc((size + 1) * sizeof(char));
			if (!wd)
				return ;
		}
		else
			break ;
	}
	printf("%s\n", wd);
	free(wd);
}
