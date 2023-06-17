/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:43:20 by hakim             #+#    #+#             */
/*   Updated: 2023/06/16 11:48:53 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

char	*_getcwd(void)
{
	char	*wd;
	size_t	size;
	DIR		*dir;

	size = 50;
	wd = (char *) malloc((size + 1) * sizeof(char));
	if (!wd)
		perror_exit("malloc");
	dir = opendir(".");
	if (!readdir(dir))
		return (free(wd), NULL);
	closedir(dir);
	while (!getcwd(wd, size))
	{
		size += 10;
		free(wd);
		wd = (char *) malloc((size + 1) * sizeof(char));
		if (!wd)
			perror_exit("malloc");
	}
	return (wd);
}

void	ft_pwd(t_list *args)
{
	char	*wd;

	(void) args;
	wd = _getcwd();
	if (!wd)
		return ((void) printf("error: current directory doesn't exist\n"));
	printf("%s\n", wd);
	free(wd);
}
