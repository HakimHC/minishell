#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

int	main(void)
{
	char	*line;

	line = readline("minishell$ ");
	while (ft_strncmp(line, "exit", 4))
	{
		printf("Line read: %s\n", line);
		add_history(line);
		t_list *tokens = split_line(line);
		(void) tokens;
		free(line);
		line = readline("minishell$ ");
	}
	free(line);
	return (0);
}
