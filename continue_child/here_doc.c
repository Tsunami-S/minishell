/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:21:35 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/15 22:07:16 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_filename(t_child *child, char *basename, int i)
{
	char	*index;
	char	*filename;

	index = ft_itoa(i);
	if (!index)
		exit_child(child, EXIT_FAILURE, errno,
			"cannot create temp file for here-document");
	filename = ft_strjoin(basename, index);
	free(index);
	if (!filename)
		exit_child(child, EXIT_FAILURE, errno,
			"cannot create temp file for here-document");
	return (filename);
}

static char	*get_filename(t_child *child)
{
	char	*filename;
	char	*basename;
	int		i;

	basename = ft_strdup("/tmp/.tmp");
	if (!basename)
		exit_child(child, EXIT_FAILURE, errno,
			"cannot create temp file for here-document");
	filename = basename;
	while (!access(filename, F_OK))
	{
		i = 0;
		while (i <= INT_MAX)
		{
			filename = make_filename(child, basename, i);
			if (access(filename, F_OK))
				break ;
			free(filename);
			i++;
		}
		free(basename);
		basename = filename;
	}
	return (filename);
}

static int	open_tmpfile(t_child *child, char **filename)
{
	int	fd;

	if (!*filename)
		*filename = get_filename(child);
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_child(child, EXIT_FAILURE, errno, *filename);
	return (fd);
}

char	*heredoc(t_child *child, char *limiter)
{
	int			lim_len;
	int			filefd;
	char		*buf;
	static char	*filename;

	filefd = open_tmpfile(child, &filename);
	lim_len = ft_strlen(limiter);
	while (1)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf)
			break ;
		else if (!ft_strncmp(limiter, buf, lim_len))
		{
			free(buf);
			break ;
		}
		ft_putendl_fd(buf, filefd);
		free(buf);
	}
	if (close(filefd) == -1)
		exit_child(child, EXIT_FAILURE, errno, filename);
	return (filename);
}
