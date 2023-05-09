/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:21:09 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/09 17:03:25 by hakahmed         ###   ########.fr       */
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

unsigned char exec_builtin(char *cmd, t_list *args)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp((data->builtins->cmd)[i], cmd))
		{
			(data->builtins->f)[i](args);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_execute(char *cmd, t_list *_args)
{
	char **args;
	char *cmd_path;

	if (!cmd || exec_builtin(cmd, _args))
		exit(0);
	args = list_to_arr(_args);
	if (!ft_abs_path(cmd))
		cmd_path = get_cmd(path_arr(), cmd, 1);
	else
		cmd_path = cmd;
	if (!cmd_path)
		exit(127);
	args[0] = ft_strdup(cmd_path);
	if (access(cmd_path, F_OK))
		exit(127);
	execve(cmd_path, args, data->envparr);
	exit(0);
	ft_free_strarr(args);
	if (cmd_path != cmd)
		free(cmd_path);
	exit(errno);
}
