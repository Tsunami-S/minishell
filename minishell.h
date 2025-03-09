/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:11:26 by haito             #+#    #+#             */
/*   Updated: 2025/03/10 00:07:43 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>

typedef enum e_kind
{
	WORD,
	REDIRECT,
}	t_kind;

typedef struct s_tokens
{
	char *token;
	t_kind kind;
	struct s_tokens *next;
}	t_tokens;

typedef struct s_redirect
{
	t_kind kind;
	char *fd;
	char *to_file;
	char *limiter;
	struct s_redirect *next;
}	t_redirect;

typedef struct s_var
{
	char *name;
	char *value;
	struct s_var *next;
}	t_var;


typedef struct s_status
{
	int		last_exit_status;
	char	*location;
}	t_status;

char	**init_sep(void);
pid_t	*make_pipe(char **cmds, int sizeof_pipe, char **envp);

void	error_process();
void	free_pipefd(int **pipefd, int i);

size_t	ft_strlen(const char *s);
int		ft_strlen_sep(const char *str, const char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
size_t	ft_strncpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	**ft_split(const char *str, char c);
char	**ft_split_sep(const char *str, char **sep, int length);
int		count_words(const char *str, char c);
int	count_sep(const char *str, char **sep, int length, int count);

/* added by tsunami */
size_t	ft_strlcat(char *dst, const char *src, size_t dsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dsize);
int	ft_isspace(char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
char	*ft_strndup(const char *s, int n);
void	continue_child(char *str, char **envp);
void	make_fullpath(char *cmd, char **envp, char **fullpath);
t_tokens	*tokenizer(char *str);

#endif
