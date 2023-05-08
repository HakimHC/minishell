/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 01:47:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/04 02:28:25 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

void	expand_cmd(t_cmdtab *tab)
{
	char	*var;
	char	*temp;
	char	*env;
	int	i;

	var = NULL;
	if (ft_strchr(tab->cmd, '$'))
		var = ft_strdup(ft_strchr(tab->cmd, '$') + 1);
	else
		return ;
	env = ft_getenv(var);
	ft_printf("env: %s\n", env);
	free(var);
	i = -1;
	while ((tab->cmd)[++i] != '$');
	temp = ft_substr(tab->cmd, 0, i + 1);
	if (!temp)
		return ;
	var = ft_strjoin(temp, env);
	free(temp);
	free(env);
	ft_printf("var: %s\n", var);
}

void	expander(void)
{
	////
}
