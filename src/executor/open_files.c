/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:29:59 by hakim             #+#    #+#             */
/*   Updated: 2023/05/13 21:30:24 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "minishell.h"

int	open_infile(t_cmdtab *tab)
{
	t_list *lst;
	t_redir *file;
	int	fd;

	lst = tab->redir_in;
	if (!lst)
		return (STDIN_FILENO);
	while (lst)
	{
		file = lst->content;
		if (file->type == HEREDOC)
			fd = handle_heredoc(file->file);
		else
			fd = open(file->file, O_RDONLY);
		if (fd < 0)
			perror(file->file);
		if (lst->next && fd > 0)
			close(fd);
		lst = lst->next;
	}
	return (fd);
}

int	open_with_flags(char *file, int type)
{
	int	flags;
	int	fd;

	flags = O_CREAT | O_WRONLY;
	if (type == REDIR_OUT)
		flags = flags | O_TRUNC;
	if (type == APPEND)
		flags = flags | O_APPEND;
	fd = open(file, flags, 0644);
	return (fd);

}

int	open_outfile(t_cmdtab *tab)
{
	t_list *lst;
	t_redir *file;
	int	fd;

	lst = tab->redir_out;
	if (!lst)
		return (STDOUT_FILENO);
	while (lst)
	{
		file = lst->content;
		fd = open_with_flags(file->file, file->type);
		if (fd < 0)
			perror(file->file);
		if (lst->next)
			close(fd);
		lst = lst->next;
	}
	return (fd);
}
