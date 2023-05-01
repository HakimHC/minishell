/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:28:50 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/01 22:45:32 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

int	ft_abs_path(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] != '.' && cmd[0] != '~' && cmd[0] != '/')
		return (0);
	if (!access(cmd, X_OK))
		return (1);
	return (0);
}

char	**split_path(char *path)
{
	char	**arr;
	char	*aux;
	int		i;

	arr = ft_split(path, ':');
	i = 0;
	while (arr[i])
	{
		aux = arr[i];
		arr[i] = ft_strjoin(arr[i], "/");
		free(aux);
		i++;
	}
	return (arr);
}

char	**path_arr(void)
{
	char	*path;
	char	**arr_path;

	path = ft_getenv("PATH");
	if (!path)
		return (NULL);
	arr_path = split_path(path);
	return (arr_path);
}

char	*get_cmd(char *path[], char *cmd, int b)
{
	int		i;
	char	*check;

	i = 0;
	while (path && path[i] && cmd)
	{
		check = ft_strjoin(path[i], cmd);
		if (!access(check, F_OK))
			return (ft_free_strarr(path), check);
		free(check);
		i++;
	}
	if (path)
		ft_free_strarr(path);
	if (b)
	{
		ft_putstr_fd("command not found: ", 2);
		if (cmd)
			ft_putendl_fd(cmd, 2);
		else
			ft_putendl_fd("", 2);
	}
	return (NULL);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*path;
// 	char	**arr;
//
// 	path = get_path(envp);
// 	arr = split_path(path);
// 	ft_printf("%d\n", access_check(arr, argv[1]));
// }
