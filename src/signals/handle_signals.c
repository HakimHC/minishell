/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:42:58 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/11 17:44:19 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "minishell.h"

void	handle_sigquit(int sig)
{
	(void) sig;
	close(STDIN_FILENO);
}

void	sighandler(void)
{
	signal(SIGQUIT, &handle_sigquit);
}