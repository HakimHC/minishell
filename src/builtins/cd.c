/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:44:16 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/15 04:57:18 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

void	go_home(void)
{
	char	*home;
	char	*old_pwd;
	char	*aux;

	home = ft_getenv("HOME");
	if (!home)
		return (ft_putendl_fd("cd: HOME not set", 2));
	old_pwd = _getcwd();
	if (!old_pwd)
		old_pwd = ft_strdup("");
	chdir(home);
	aux = old_pwd;
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(aux);
	ft_setenv(old_pwd);
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
	if (args && chdir(args->content) == -1)
		perror(args->content);
}
