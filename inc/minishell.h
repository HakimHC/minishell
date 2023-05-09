#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1
# define HEREDOC 0b1
# define APPEND 0b10
# define PIPE_IN 0b100
# define PIPE_OUT 0b1000
# define REDIR_IN 0b10000
# define REDIR_OUT 0b100000

# include <unistd.h>

# include "../libft/inc/libft.h"

typedef struct s_redir
{
	char	*file;
	int	type;
}	t_redir;

typedef struct  s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_cmdtab
{
	char	*cmd;
	t_list	*args;
	t_list	*redir_in;
	t_list	*redir_out;
	int	*flags;
	struct s_cmdtab *next;
}	t_cmdtab;

typedef struct s_builtin
{
	char	*cmd[7];
	void	(*f[7])(t_list *);
}	t_builtin;

typedef struct s_data
{
	t_cmdtab	*cmdtab;
	t_list		*tokens;
	t_list		*envp;
	t_builtin	*builtins;
	char		**envparr;
	int		fdo;
}	t_data;

/* global */

extern t_data *data;

/* main */

void	cmd_listen(char *prompt);
void	destroyer(void);

/* lexer */
int	tokenize_input(char *input);
int	is_special_char(char c);
t_list	*split_line(char *line);

/* parser */
void	fill_cmdtab(void);
void	print_cmdtab(void);
t_cmdtab	*cmdtab_init(void);
int	*set_flags(t_data *data);
void	populate(t_data *data);
int	pipe_parse_error(void);
int	input_syntax_errors(void);
unsigned char is_redir(char *token);
int	redir_parse_error(void);
int	print_token_error(char *token);
int	pre_token_parse_error(char *input);

/* executor */
void	ft_execute(char *cmd, t_list *_args);
int	ft_open(char *file, int oflags);
void	ft_pipe(int fd[2]);
pid_t	ft_fork(void);
char	**list_to_arr(t_list *head);
void	perror_exit(char *str);
void	executor(t_cmdtab *tab);
char	**split_path(char *path);
char	*get_cmd(char *path[], char *cmd, int b);
char	**path_arr(void);
int	ft_abs_path(char *cmd);

/* builtins */
void	ft_env(t_list *args);
t_list	*envars_to_list(char *envp[]);
char	**list_to_envars(t_list *head);
void	ft_export(t_list *arg);
void	ft_unsetenv(char *var);
void	ft_setenv(char *arg);
void	ft_unset(t_list *args);
char	*ft_getenv(char *arg);
void	ft_echo(t_list	*args);
void	ft_pwd(t_list *args);
void	ft_cd(t_list *args);
void	print_env(t_list *head);
t_list	*parse_envar(char *envar);
unsigned char export_error(char *arg);
unsigned char exec_builtin(char *cmd, t_list *args);
int is_int(char *str);
void	ft_exit(t_list *args);

/* expander */
void	expand_cmd(t_cmdtab *tab);


#endif
