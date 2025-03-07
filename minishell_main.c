/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:11:19 by haito             #+#    #+#             */
/*   Updated: 2025/03/07 20:13:09 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	continue_line(char *input, char **envp)
{
	char	**cmds;
	int		exit_status;
	int		sizeof_pipe;
	char	**sep;
	// pid_t	*pids;

	sep = init_sep();
	cmds = ft_split_sep(input, sep, (int)ft_strlen(input));
	if (!cmds)
		error_process();
	sizeof_pipe = count_sep(input, sep, ft_strlen(input), 0);

	int i = 0;
	while (cmds[i])
	{
		printf("%s\n", cmds[i]);
		i++;
	}
	// pids = make_pipe(cmds, sizeof_pipe, envp);

	(void)envp;

	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);

	exit_status = 0;
	// exit_status = wait_child(sizeof_pipe, pids);
	exit(exit_status);
}

void	process_line(char *input, int *exit_status, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error_process();
	if (pid == 0)
		continue_line(input, envp);
	waitpid(pid, &status, 0);
	*exit_status = WEXITSTATUS(status);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_status	status;

	status.last_exit_status = 0;
	if (argc != 1)
		return (1);
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (0);
		if (*input)
			add_history(input);
		process_line(input, &status.last_exit_status, envp);
		free(input);
		input = NULL;
	}
	printf("exit\n");
	return (0);
}
