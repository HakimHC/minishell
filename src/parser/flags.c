/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 03:16:16 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/27 03:20:52 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define HEREDOC 0b1
#define APPEND 0b10
#define PIPE_IN 0b100
#define PIPE_OUT 0b1000

int	main(void)
{
	int	flags;

	flags = HEREDOC | APPEND | PIPE_OUT;
	if ((flags & HEREDOC) != 0)
		printf("HEREDOC ENABLED\n");
	if ((flags & APPEND) != 0)
		printf("APPEND ENABLED\n");
	if ((flags & PIPE_IN) != 0)
		printf("PIPE_IN ENABLED\n");
	if ((flags & PIPE_OUT) != 0)
		printf("PIPE_OUT ENABLED\n");
}
