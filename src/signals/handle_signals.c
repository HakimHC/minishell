/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:42:58 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/12 01:24:06 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/rlstdc.h>
#include <signal.h>
#include <unistd.h>

#include "minishell.h"

void	handle_sigquit(int sig)
{
	(void) sig;
	close(STDIN_FILENO);
}

void	handle_sigint(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighandler(void)
{
	signal(SIGQUIT, &handle_sigquit);
	signal(SIGINT, &handle_sigint);
}
