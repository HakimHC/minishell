/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:43:20 by hakim             #+#    #+#             */
/*   Updated: 2023/05/01 18:29:10 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	ft_pwd(void)
{
	char	*wd;
	size_t	size;

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
