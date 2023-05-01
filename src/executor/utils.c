/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:21:09 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/01 14:39:05 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

#include "minishell.h"

void	perror_exit(char *str)
{
	perror(str);
	exit(errno);
}

char	**list_to_arr(t_list *head)
{
	t_list	*curr;
	char	**arr;
	int	size;
	int	i;

	size = ft_lstsize(head);
	arr = (char **) malloc((size + 2) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 1;
	curr = head;
	while (curr)
	{
		arr[i] = ft_strdup(curr->content);
		i++;
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}

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

void	ft_execute(char *cmd, t_list *_args)
{
	char **args;
	char *cmd_path;
	pid_t pid;

	args = list_to_arr(_args);
	if (!ft_abs_path(cmd))
		cmd_path = get_cmd(path_arr(), cmd, 1);
	else
		cmd_path = cmd;
	args[0] = ft_strdup(cmd_path);
	if (!cmd_path)
		exit(127);
	pid = ft_fork();
	if (!pid)
		execve(cmd_path, args, data->envp);
	waitpid(pid, NULL, 1);
}
