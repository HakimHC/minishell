/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:32:56 by hakim             #+#    #+#             */
/*   Updated: 2023/05/13 21:33:05 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char is_builtin(char *cmd)
{
	int	i;
	char	*str;

	if (!cmd)
		return (0);
	i = 0;
	while (i < 7)
	{
		str = (data->builtins->cmd)[i];
		if (!ft_strncmp(cmd, str, ft_strlen(cmd) + 1))
			return (1);
		i++;
	}
	return (0);
}

