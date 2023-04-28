/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/27 21:04:39 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "minishell.h"

void	open_file(char *file, t_cmdtab *tab)
{
	t_redir *lst;

	lst = tab->redir_in->content;
}

void	executor(void)
{
	int		fd;
	t_cmdtab	*cmdtab;


}
