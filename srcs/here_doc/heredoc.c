/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:00:07 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/30 20:17:33 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_filename(char *basename, int i)
{
	char	*index;
	char	*file;

	index = ft_itoa(i);
	if (!index)
		return (perror("minishell: malloc failed"), NULL);
	file = ft_strjoin(basename, index);
	free(index);
	if (!file)
		return (perror("minishell: malloc failed"), NULL);
	return (file);
}

static char	*get_filename(void)
{
	char	*file;
	char	*basename;
	int		i;

	basename = ft_strdup("/tmp/.tmp");
	if (!basename)
		return (perror("minishell: malloc failed"), NULL);
	file = basename;
	while (!access(file, F_OK))
	{
		i = 0;
		while (i <= INT_MAX)
		{
			file = make_filename(basename, i);
			if (access(file, F_OK))
				break ;
			free(file);
			i++;
		}
		free(basename);
		basename = file;
	}
	return (file);
}

static int	open_tmpfile(char **file)
{
	int	fd;

	if (!*file)
		*file = get_filename();
	if (!*file)
		return (ERROR);
	fd = open(*file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free(*file), perror("minishell: open failed"), -1);
	return (fd);
}

static void	heredoc_loop(int filefd, char *limiter, t_var **varlist)
{
	char	*buf;
	int		lim_len;

	lim_len = ft_strlen(limiter);
	while (1)
	{
		buf = readline("> ");
		if (g_signal == SIGINT || (buf && !lim_len && !*buf) 
				|| (buf && lim_len && !ft_strncmp(limiter, buf, lim_len)))
		{
			free(buf);
			break ;
		}
		else if (!buf)
		{
			ft_eprintf("minishell: warning: here-document wanted `%s'\n",
				limiter);
			break ;
		}
		buf = heredoc_expand_var(buf, varlist);
		ft_putendl_fd(buf, filefd);
		free(buf);
	}
}

char	*here_doc(char *limiter, t_var **varlist)
{
	int		filefd;
	char	*file;

	filefd = open_tmpfile(&file);
	if (filefd == -1)
		return (NULL);
	if (signal(SIGINT, sig_handler_heredoc) == SIG_ERR)
		return (perror("minishell: signal"), NULL);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (perror("minishell: signal"), NULL);
	heredoc_loop(filefd, limiter, varlist);
	if (signal(SIGINT, sig_handler_inprocess) == SIG_ERR)
		return (perror("minishell: signal"), NULL);
	if (signal(SIGQUIT, sig_handler_inprocess) == SIG_ERR)
		return (perror("minishell: signal"), NULL);
	if (g_signal == SIGINT)
		g_signal = 0;
	if (close(filefd) == -1)
		return (perror("minishell: close failed"), free(file), NULL);
	return (file);
}
