/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:52:57 by hakim             #+#    #+#             */
/*   Updated: 2023/04/29 19:59:17 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

t_data	*data;

int	main(int argc, char **argv)
{
	extern char	**environ;
	char		*line;

	if (argc != 2)
	{
		printf("usage: arg1\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		exit(69);
	data->envp = environ;
	line = argv[1];
	add_history(line);
	if (pre_token_parse_error(line))
	{
		printf("input sytnax err\n");
		exit(1);
	}
	if (!tokenize_input(line))
	{
		fill_cmdtab();
		print_cmdtab();
		executor(data->cmdtab);
	}
	return (0);
}
