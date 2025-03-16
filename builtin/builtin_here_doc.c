/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:09:01 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/16 16:14:36 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_filename(char *basename, int i)
{
	char	*index;
	char	*file;

	index = ft_itoa(i);
	if (!index)
	{
		builtin_error(errno, "cannot create temp file for here-document");
		return (NULL);
	}
	file = ft_strjoin(basename, index);
	free(index);
	if (!file)
	{
		builtin_error(errno, "cannot create temp file for here-document");
		return (NULL);
	}
	return (file);
}

static char	*get_filename(void)
{
	char	*file;
	char	*basename;
	int		i;

	basename = ft_strdup("/tmp/.tmp");
	if (!basename)
	{
		builtin_error(errno, "cannot create temp file for here-document");
		return (NULL);
	}
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
		return (EXIT_FAILURE);
	fd = open(*file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (builtin_error(errno, *file));
	return (fd);
}

static int	builtin_heredoc(char **tmpfile, char *limiter)
{
	int		lim_len;
	int		filefd;
	char	*buf;

	filefd = open_tmpfile(tmpfile);
	if (filefd < 0)
		return (EXIT_FAILURE);
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
		return (builtin_error(errno, *tmpfile));
	return (SUCCESS);
}

int	check_here_doc(t_tokens **tokens, char **tmpfile)
{
	t_tokens	*head;
	int			status;

	head = *tokens;
	while (head)
	{
		if (head->type == HEREDOC)
		{
			status = builtin_heredoc(tmpfile, head->next->token);
			if (status != SUCCESS)
			{
				unlink(*tmpfile);
				free(*tmpfile);
				return (EXIT_FAILURE);
			}
		}
		head = head->next;
	}
	return (EXIT_SUCCESS);
}
