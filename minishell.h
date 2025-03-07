/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:11:26 by haito             #+#    #+#             */
/*   Updated: 2025/03/07 14:55:41 by haito            ###   ########.fr       */
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
char	*ft_strdup(const char *s);
char	**ft_split(const char *str, char c);
char	**ft_split_sep(const char *str, char **sep, int length);
int		count_words(const char *str, char c);


#endif