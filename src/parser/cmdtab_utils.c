/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:11:17 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/27 19:11:53 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmdtab(void)
{
	t_list *curr;
	t_cmdtab *cmd_curr;
	cmd_curr = data->cmdtab;
	while (cmd_curr)
	{
		ft_putstr("\n==============================\n");
		ft_printf("COMMAND: %s\n", cmd_curr->cmd);
		ft_putstr("\n==============================\n");
		ft_putstr("ARGS: ");
		print_list(cmd_curr->args,0);
		ft_putstr("\n==============================\n");
		curr = cmd_curr->redir_in;
		ft_putstr("REDIR IN:\n");
		while (curr)
		{
			ft_printf("FILE: %s\nTYPE: %d\n", ((char *)((t_redir*) (curr->content))->file),
					((t_redir*)(curr->content))->type);
			curr = curr->next;
		}
		curr = cmd_curr->redir_out;
		ft_putstr("\n==============================\n");
		ft_putstr("REDIR OUT:\n");
		while (curr)
		{
			ft_printf("FILE: %s\nTYPE: %d\n", ((char *)((t_redir*) (curr->content))->file),
					((t_redir*)(curr->content))->type);
			curr = curr->next;
		}
		ft_putstr("\n==============================\n");
		ft_putstr("PIPE\n");
		cmd_curr = cmd_curr->next;
	}
}

void	fill_cmdtab(void)
{
	data->cmdtab = cmdtab_init();
	populate(data);
}

