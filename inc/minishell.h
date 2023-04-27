#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1

# include "libft.h"

typedef struct s_cmdtab
{
	char	*cmd;
	t_list	*args;
	char	*redir_in;
	char	*redir_out;
	int	flags;
}	t_cmdtab;

/* lexer */
int	is_special_char(char c);
t_list	*split_line(char *line);

#endif
