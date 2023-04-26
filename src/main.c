#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

int	main(void)
{
	char	*line;

	line = readline("8====D $> ");
	while (ft_strncmp(line, "exit", 4))
	{
		printf("Line read: %s\n", line);
		add_history(line);
		free(line);
		line = readline("8====D $> ");
	}
	free(line);
	rl_clear_history();
	return (0);
}
