/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:21:35 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/18 22:06:14 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_filename(t_child *child, char *basename, int i)
{
	char	*index;
	char	*file;

	index = ft_itoa(i);
	if (!index)
		exit_child(child, EXIT_FAILURE, errno,
			"cannot create temp file for here-document");
	file = ft_strjoin(basename, index);
	free(index);
	if (!file)
		exit_child(child, EXIT_FAILURE, errno,
			"cannot create temp file for here-document");
	return (file);
}

static char	*get_filename(t_child *child)
{
	char	*file;
	char	*basename;
	int		i;

	basename = ft_strdup("/tmp/.tmp");
	if (!basename)
		exit_child(child, EXIT_FAILURE, errno,
			"cannot create temp file for here-document");
	file = basename;
	while (!access(file, F_OK))
	{
		i = 0;
		while (i <= INT_MAX)
		{
			file = make_filename(child, basename, i);
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

static int	open_tmpfile(t_child *child, char **file)
{
	int	fd;

	if (!*file)
		*file = get_filename(child);
	fd = open(*file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_child(child, EXIT_FAILURE, errno, *file);
	return (fd);
}

char	*child_heredoc(t_child *child, char *limiter, t_type type,
		t_var **varlist)
{
	int			lim_len;
	int			filefd;
	char		*buf;
	static char	*file;

	filefd = open_tmpfile(child, &file);
	lim_len = ft_strlen(limiter);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		else if (!ft_strncmp(limiter, buf, lim_len))
		{
			free(buf);
			break ;
		}
		if (type == WORD)
			buf = heredoc_expand_var(buf, varlist);
		ft_putendl_fd(buf, filefd);
		free(buf);
	}
	if (close(filefd) == -1)
		exit_child(child, EXIT_FAILURE, errno, file);
	return (file);
}
