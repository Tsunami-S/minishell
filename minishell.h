/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hito <hito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:11:26 by haito             #+#    #+#             */
/*   Updated: 2025/03/19 16:35:36 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/wait.h>
# include "error_num.h"
# include "ft_eprintf/ft_eprintf.h"

# define MAX_STACK_BRACKETS 500

typedef struct s_saved
{
	int in;
	int out;
}	t_saved;

typedef enum e_exist
{
	NONE,
	EXIST,
}	t_exist;

typedef enum e_type
{
	WORD,
	TRUNC,
	APPEND,
	INPUT,
	HEREDOC,
	HAVE_QUOTE,
}	t_type;

typedef struct s_tokens
{
	char			*token;
	t_type			type;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_child
{
	t_var		**varlist;
	t_tokens	**tokens;
	char		**cmds;
	char		*fullpath;
	char		**envp;
	char		**paths;
	char		*tmpfile;
}	t_child;

typedef struct s_status
{
	struct s_status	*previous;
	char			*cmds;
	t_tokens		*token;
	pid_t			pid;
	pid_t			input_pipefd;
	pid_t			output_pipefd;
	int				has_brackets;
	int				has_or;
	int				has_and;
	int				is_builtin;
	struct s_status	*next;
}	t_status;

typedef struct s_brackets
{
	int	top;
	int	data[MAX_STACK_BRACKETS + 1];
	int	pair[MAX_STACK_BRACKETS + 1][2];
	int	countof_pair;
	int	location;
}	t_brackets;

typedef struct s_parser
{
	int		i;
	char	*cmds;
}	t_parser;

typedef struct s_last_process
{
	pid_t		last_pid;
	int			result;
	int			count_forked;
}	t_lp;

char	**init_builtin_cmds(void);
void	free_builtin_cmds(char **builtin_cmds);

size_t	ft_strlen(const char *s);
int		ft_strlen_sep(const char *str, const char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
size_t	ft_strncpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	**ft_split(const char *str, char c);
char	**ft_split_sep(const char *str, char **sep, int length);
int		count_words(const char *str, char c);
int		count_sep(const char *str, char **sep, int length, int count);

int	find_brackets_pair(const char *input, t_brackets *b, int length);
int	get_brackets_pair(int i, t_brackets *brackets);
int	add_operator_node(const char *op, char **cmds, t_status **st_head, int i);
t_status	*ft_new_node(const char *cmds, int has_brackets);
void	ft_add_back_node(t_status **head, t_status *new_node);
void	ft_remove_node(t_status **head, t_status *node);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	ft_strcpy(char *new_str, char *str);
int	continue_line(char *input, t_var **varlist);
/* added by haruki */
//changed
char	*trim_spaces(char *str);
char	*add_char(char *cmds, char c, int *i);
int		add_command_node(char **cmds, t_status **st_head);
t_status	*sep_input_to_cmds(const char *input, t_brackets *brackets,
	t_status *st_head);
	int	make_pipe(t_status **st_head);
	int	fork_and_wait(t_status **st_head, t_var **varlist);
	
//new
void	*error_add_char(int *i, char *cmds);
void	free_lst_status(t_status *st_head, t_status *st);
int		error_handle_brackets(int error_num);
int		error_node(int error_num);
int		error_pipe(int error_num);
int	call_builtin(t_tokens **tokens, t_var **varlist, t_status *st_head);
void	handle_and_or(t_status *st, t_lp *lp);
void	handle_parent_process(t_status *st);
void	handle_child_process(t_status *st, t_var **varlist, t_status *st_head);
int	builtin_cd(t_tokens **tokens);
int	builtin_pwd(void);
int	builtin_exit(t_tokens **tokens, t_var **varlist, t_status *st_head);
void	frees(t_status *st_head, t_var **varlist);
int	recursive_continue_line(char *input, t_var **varlist);
int	child_call_builtin(t_tokens **tokens, t_var **varlist, t_status *st_head);
int	ft_atoi(const char *str);

/* added by tsunami */
size_t	ft_strlcat(char *dst, const char *src, size_t dsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dsize);
int	ft_isspace(char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
char	*ft_strndup(const char *s, int n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void free_strs(char **strs);
int	ft_isalnum(int c);
int	ft_isdigit(int c);

/* set varlist */
//t_var	*init_varlist(char **envp);
t_var	*init_varlist(char **envp, char *c1, char *c2);
void	free_varlist(t_var **varlist);
t_var	*get_var(t_var **varlist, char *name);
void	add_var(t_var **varlist, char *var_name, char *var_value);

/* expander */
t_tokens	*expander(char *str, t_var **varlist);
t_tokens	*pre_tokenizer(char *str);
int more_tokenizer(t_tokens **tokens);
int	replace_vars(t_tokens **tokens, t_var **varlist);
char *count_plaintext_size(char *str);
int	count_words_and_vars(char *str);
char	**split_token(char *token, int malloc_size, t_var **varlist);
char	*skip_space(char *str);;
/* continue_child */
void	continue_child(t_tokens **tokens, t_var **varlist);
void	redirect_fds(t_child *child, t_tokens **tokens, t_var **varlist);
char	*child_heredoc(t_child *child, char *limiter, t_type type, t_var **varlist);
void	make_cmds(t_child *child, t_tokens **tokens);
void	make_envp(t_child *child, t_var **varlist);
void	make_fullpath(t_child *child, char *cmd, t_var **varlist);
void	exit_child(t_child *child, int status, int errnum, char *msg);

/* here_doc */
char *heredoc_expand_var(char *buf, t_var **varlist);
int	heredoc_vars_count(char *str);
char	**heredoc_split_token(char *token, int malloc_size, t_var **varlist);

/* others */
void free_tokens(t_tokens **tokens);
void 	free_one_token(t_tokens **tokens, t_tokens *rm_token);
void	free_words(char **words, int size);

/* builtin */
int	redirect_builtin(t_tokens **tokens, t_saved *saved, t_var **varlist);
int	check_here_doc(t_tokens **tokens, char **tmpfile, t_var **varlist);
int	builtin_save_stdio(t_tokens **tokens, t_saved *saved);
int	builtin_reset_stdio(t_saved *saved);
int builtin_error(int errnum, char *msg);
int builtin_unset(t_tokens **tokens, t_var **varlist);
int	builtin_env(t_tokens **tokens, t_var **varlist);
int	builtin_export(t_tokens **tokens, t_var **varlist);
int builtin_export_list(t_var **varlist);
int	builtin_echo(t_tokens **tokens, t_var **varlist);

#endif
