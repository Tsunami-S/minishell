/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 07:48:56 by haito             #+#    #+#             */
/*   Updated: 2025/03/07 17:16:51 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	*init_pids(char **cmds, int sizeof_pipe, int **pipefd)
{
	pid_t	*pids;
	int		n;

	(void)cmds;


	pids = malloc((sizeof_pipe + 1) * sizeof(pid_t));
	n = 0;
	if (!pids)
	{
		perror("malloc error");
		free_pipefd(pipefd, sizeof_pipe);
		exit(1);
	}
	return (pids);
}

void	free_pipefd(int **pipefd, int i)
{
	if (!pipefd)
		return ;
	while (--i >= 0)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		free(pipefd[i]);
	}
	free(pipefd);
}

int	**init_pipefd(char **cmds, int sizeof_pipe)
{
	int	**pipefd;
	int	i;


	(void)cmds;


	i = -1;
	pipefd = malloc(sizeof_pipe * sizeof(int *));
	if (!pipefd)
		error_process();
	while (++i < sizeof_pipe)
	{
		pipefd[i] = malloc(2 * sizeof(int));
		if (!pipefd[i])
			error_process();
		if (pipe(pipefd[i]) == -1)
			error_process();
	}
	return (pipefd);
}

pid_t	*make_pipe(char **cmds, int sizeof_pipe, char **envp)
{
	int		**pipefd;
	pid_t	*pids;
	int		i;
	int		status;


(void)envp;

	i = -1;
	pipefd = init_pipefd(cmds, sizeof_pipe);
	pids = init_pids(cmds, sizeof_pipe, pipefd);
	while (++i <= sizeof_pipe)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			error_process();
		// if (pid == 0)
		// 	continue_child(pipefd, cmds, i, envp);
		while (*cmds && (ft_strcmp(*cmds, "|") != 0
				&& ft_strcmp(*cmds, "||") != 0 && ft_strcmp(*cmds, "&&") != 0))
		cmds++;
		if (*cmds && !ft_strcmp(*cmds, "||"))
		{
			wait(&status);
			if (WEXITSTATUS(status) == 0)
				break ;
		}
		if (*cmds && !ft_strcmp(*cmds, "&&"))
		{
			wait(&status);
			if (WEXITSTATUS(status) != 0)
				break ;
		}
		cmds++;
	}
	free_pipefd(pipefd, sizeof_pipe);
	return (pids);
}
