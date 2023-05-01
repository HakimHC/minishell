/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:30:22 by hakim             #+#    #+#             */
/*   Updated: 2023/05/01 21:40:23 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

t_list	*envars_to_list(char *envp[])
{
	t_list	*head;

	if (!(*envp))
		return (NULL);
	/* ft_printf("%s\n", *envp); */
	head = ft_lstnew(ft_strdup(*envp));
	head->next = envars_to_list(envp + 1);
	return (head);
}

char	**list_to_envars(t_list *head)
{
	char	**envars;
	int	i;

	envars = (char **) malloc((ft_lstsize(head) + 1) * sizeof(char *));
	if (!envars)
		return (NULL);
	i = 0;
	while (head)
	{
		envars[i] = ft_strdup(head->content);
		i++;
		head = head->next;
	}
	envars[i] = NULL;
	ft_lstclear(&head, &free);
	return (envars);
}

char	*ft_getenv(char *arg)
{
	int	i;

	arg = ft_strjoin(arg, "=");
	if (!arg)
		return (NULL);
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], arg, ft_strlen(arg)))
			return (ft_strdup(ft_strchr(data->envp[i], '=') + 1));
		i++;
	}
	return (NULL);
}

void	ft_export(char *arg)
{
	t_list	*envar_list;

	envar_list = envars_to_list(data->envp);
	if (!envar_list)
	{
		ft_printf("fatal: malloc() failed\n");
		return ;
	}
	ft_free_strarr(data->envp);
	ft_lstadd_back(&envar_list, ft_lstnew(ft_strdup(arg)));
	data->envp = list_to_envars(envar_list);
}
