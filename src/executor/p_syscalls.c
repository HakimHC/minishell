/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_syscalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:36:08 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/10 21:36:36 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror_exit("fork");
	return (pid);
}

void	ft_pipe(int fd[2])
{
	int	p;

	p = pipe(fd);
	if (p < 0)
		perror_exit("pipe");
}

int	ft_open(char *file, int oflags)
{
	int	fd;

	fd = open(file, oflags, 0644);
	if (fd < 0)
		perror_exit(file);
	return (fd);
}
