/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:11:26 by haito             #+#    #+#             */
/*   Updated: 2025/03/15 20:55:47 by tssaito          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/wait.h>
# include "error_num.h"
# include "ft_eprintf/ft_eprintf.h"

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
}	t_type;

typedef struct s_tokens
{
	char *token;
	t_type type;
	struct s_tokens *next;
}	t_tokens;

typedef struct s_var
{
	char *name;
	char *value;
	struct s_var *next;
}	t_var;

typedef struct s_child
{
	t_var		**varlist;
	t_tokens	**tokens;
	char		**cmds;
	char		*fullpath;
	char		**envp;
	char		**paths;
}	t_child;


// typedef struct s_status
// {
// 	int		last_exit_status;
// 	char	*location;
// }	t_status;

// added_by_haito
typedef struct s_status
{
	struct s_status	*previous;
	char			*cmds;
	pid_t			pid;
	pid_t			input_pipefd;
	pid_t			output_pipefd;
	int				has_brackets;
	int				has_or;
	int				has_and;
	int				is_builtin;
	struct s_status	*next;
	t_tokens *token;
}	t_status;

# define MAX_STACK_BRACKETS 500

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

char	**init_builtin_cmds(void);
void	error_process();
void	free_brackets();
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
t_status	*sep_input_to_cmds(const char *input, t_brackets *brackets);
t_status	*ft_new_node(const char *cmds, int has_brackets);
void	ft_add_back_node(t_status **head, t_status *new_node);
void	ft_remove_node(t_status **head, t_status *node);
void	add_command_node(char **cmds, t_status **st_head);
int	add_operator_node(const char *op, char **cmds, t_status **st_head, int i);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*add_char(char *cmds, char c);
void	ft_strcpy(char *new_str, char *str);
char *trim_spaces(const char *str, size_t i, size_t j);
void	make_pipe(t_status **st_head);
int	continue_line(char *input, t_var **varlist);
void	fork_and_wait(t_status **st_head, t_var **varlist);

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
char	*get_next_line(int fd);
void free_strs(char **strs);

/* set varlist */
t_var	*init_varlist(char **envp);
void	free_varlist(t_var **varlist);
t_var	*get_var(t_var **varlist, char *name);
void	add_var(t_var **varlist, char *var_name, char *var_value);
t_var	**remove_var(t_var **varlist, char *name);

/* expander */
t_tokens	*expander(char *str, t_var **varlist);
t_tokens	*tokenizer(char *str);
void	replace_vars(t_tokens **tokens, t_var **varlist);
char *count_plaintext_size(char *str);
int	count_words_and_vars(char *str);
char	**split_token(char *token, int malloc_size, t_var **varlist);

/* continue_child */
void	continue_child(t_tokens **tokens, t_var **varlist);
void	redirect_fds(t_child *child, t_tokens **tokens);
char	*heredoc(t_child *child, char *limiter);
void	make_cmds(t_child *child, t_tokens **tokens);
void	make_envp(t_child *child, t_var **varlist);
void	make_fullpath(t_child *child, char *cmd, t_var **varlist);
void	exit_child(t_child *child, int status, int errnum, char *msg);

/* others */
void free_tokens(t_tokens **tokens);
void	free_words(char **words, int size);


#endif
