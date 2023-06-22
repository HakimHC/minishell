/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:44:16 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/22 21:28:19 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"

int	change_dir(char *dir)
{
	char	*pwd;
	char	*aux;
	char	*old_pwd;

	old_pwd = _getcwd();
	if (!old_pwd)
		old_pwd = ft_strdup("");
	if (chdir(dir) == -1)
		return (free(old_pwd), perror(dir), -1);
	aux = old_pwd;
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(aux);
	ft_setenv(old_pwd);
	pwd = _getcwd();
	if (!pwd)
		pwd = ft_strdup("");
	aux = pwd;
	pwd = ft_strjoin("PWD=", pwd);
	free(aux);
	ft_setenv(pwd);
	free(pwd);
	free(old_pwd);
	return (0);
}

void	go_home(void)
{
	char	*home;

	home = ft_getenv("HOME");
	if (!home)
		return (ft_putendl_fd("cd: HOME not set", 2));
	change_dir(home);
}

void	expand_home(char *path)
{
	char	*home;
	char	*res;
	char	*tmp;

	home = ft_getenv("HOME");
	if (!home)
		return (ft_putendl_fd("cd: HOME not set", 2));
	res = ft_strjoin(home, "/");
	tmp = res;
	res = ft_strjoin(res, path + 1);
	free(tmp);
	if (chdir(res) == -1)
		perror(res);
}

void	ft_cd(t_list *args)
{
	if (!args)
		return (go_home());
	if (ft_lstsize(args) > 1)
		return (ft_putstr_fd("cd: too many arguments\n", 2));
	if (*(char *)(args->content) == '~')
		return (expand_home(args->content));
	if (change_dir(args->content) == -1)
		g_data->exit_code = 1;
}
