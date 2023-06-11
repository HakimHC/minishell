/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:23:33 by hakahmed          #+#    #+#             */
/*   Updated: 2023/06/11 19:43:00 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define SYMB 1
# define NORM 0

# include <unistd.h>

# include "libft.h"

typedef struct s_redir
{
	char	*file;
	int		type;
}			t_redir;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_token
{
	char	*content;
	int		type;
}			t_token;

typedef struct s_cmdtab
{
	char			*cmd;
	t_list			*args;
	t_list			*redir_in;
	t_list			*redir_out;
	int				*flags;
	struct s_cmdtab	*next;
}					t_cmdtab;

typedef struct s_builtin
{
	char	*cmd[7];
	void	(*f[7])(t_list *);
}			t_builtin;

typedef struct s_data
{
	t_cmdtab	*cmdtab;
	t_list		*tokens;
	t_list		*envp;
	t_builtin	*builtins;
	char		**envparr;
	int			exit_code;
}	t_data;

/* global */

extern t_data	*g_data;

/* main */

void			cmd_listen(char *prompt);
void			free_redirs(t_list *redirs);
void			free_tokens(void);
void			free_cmdtab(void);
void			destroyer(void);

/* lexer */
int				tokenize_input(char *input);
int				is_special_char(char c);
t_list			*split_line(char *line);
int				is_special_char(char c);
int				is_quote(char c);
t_list			*mk_tkn(char *input, int type);
int				mk_normal(char *input, int i, t_list **head);
int				mk_symbol(char *input, int i, t_list **head);
int				concat_tkn(char *input, int i, t_list *tkn);
int				mk_quote(char *input, int i, t_list **head);
void			print_tokens();
int				is_symb(char *token);

/* parser */
void			fill_cmdtab(void);
void			print_cmdtab(void);
t_cmdtab		*cmdtab_init(void);
int				*set_flags(t_data *data);
void			populate(t_data *data);
t_list			*p_increment(t_list *node);
int				pipe_parse_error(void);
int				input_syntax_errors(void);
unsigned char	is_redir(char *token);
int				redir_parse_error(void);
int				print_token_error(char *token);
int				pre_token_parse_error(char *input);

/* executor */
void			ft_execute(char *cmd, t_list *_args);
int				ft_open(char *file, int oflags);
void			ft_pipe(int fd[2]);
pid_t			ft_fork(void);
char			**list_to_arr(t_list *head);
void			perror_exit(char *str);
void			executor(t_cmdtab *tab);
char			**split_path(char *path);
char			*get_cmd(char *path[], char *cmd, int b);
char			**path_arr(void);
int				ft_abs_path(char *cmd);
int				handle_heredoc(char *delim);
int				open_infile(t_cmdtab *tab);
int				open_with_flags(char *file, int type);
int				open_outfile(t_cmdtab *tab);
void			handle_redirects(int redir_out, int redir_in, int pfd);
void			create_pipe(int redir_out, int redir_in, t_cmdtab *tab);
unsigned char	handle_builtin(t_cmdtab **tab);
void			wait_childs(void);
void			exec_last(int fdin, int fdout, t_cmdtab *tab);

/* builtins */
void			ft_env(t_list *args);
t_list			*envars_to_list(char *envp[]);
char			**list_to_envars(t_list *head);
void			ft_export(t_list *arg);
void			ft_unsetenv(char *var);
void			ft_setenv(char *arg);
void			ft_unset(t_list *args);
char			*ft_getenv(char *arg);
void			ft_echo(t_list	*args);
void			ft_pwd(t_list *args);
void			ft_cd(t_list *args);
void			print_env(t_list *head);
t_list			*parse_envar(char *envar);
unsigned char	export_error(char *arg);
unsigned char	exec_builtin(char *cmd, t_list *args);
int				is_int(char *str);
void			ft_exit(t_list *args);
unsigned char	is_builtin(char *cmd);

/* expander */
void			expand_cmd(t_cmdtab *tab);
char			*expand(char *token);

/* signals */
void			handle_sigquit(int sig);
void			sighandler(void);

#endif
