/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:11:19 by haito             #+#    #+#             */
/*   Updated: 2025/03/13 20:14:14 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	fork_and_wait(t_status)
// {
	
// }

void	expand_cmds(t_status **st_head)
{
	t_status	*st;
	char		*expanded_cmds;

	if (!st_head || !*st_head)
		return ;
	st = *st_head;
	while (st)
	{
		expanded_cmds = tunamis_expand(st->cmds);
		if (!expanded_cmds)
			error_process();
		free(st->cmds);
		st->cmds = expanded_cmds;
		st = st->next;
	}
}

void	check_built_in(t_status **st_head, t_status *st)
{
	char		**builtin_cmds;
	int			i;
	int			len;

	if (!st_head || !*st_head || !st)
		return ;
	builtin_cmds = init_builtin_cmds();
	while (st)
	{
		i = -1;
		while (builtin_cmds[++i])
		{
			len = ft_strlen(builtin_cmds[i]);
			if (ft_strlen(st->cmds) >= (size_t)len && !ft_strncmp(st->cmds,
					builtin_cmds[i], len) && (st->cmds[len] == '\0'
					|| st->cmds[len] == ' '))
			{
				st->is_builtin = 1;
				break ;
			}
		}
		st = st->next;
	}
	free_builtin_cmds(builtin_cmds);
}

int	continue_line(char *input, char **envp)
{
	t_status	*state;
	t_brackets	brackets;


	(void)envp;
	if (find_brackets_pair(input, &brackets) == -1)
		return (1);
	state = sep_input_to_cmds(input, &brackets);
	make_pipe(&state);
	expand_cmds(&state);
	check_built_in(&state, state);
	while (state != NULL)
	{
		printf("cmd:%s in:%d out:%d ():%d or:%d and:%d built:%d\n", state->cmds, state->input_pipefd, state->output_pipefd, state->has_brackets, state->has_or, state->has_and, state->is_builtin);
		state = state->next;
	}
	// fork_and_wait();
	return (0);
}

void	process_line(char *input, char **envp)
{
	// pid_t	pid;
	// int		status;

	// pid = fork();
	// if (pid == -1)
	// 	error_process();
	// if (pid == 0)
	continue_line(input, envp);
	// waitpid(pid, &status, 0);
	// *exit_status = WEXITSTATUS(status);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;

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
		process_line(input, envp);
		free(input);
		input = NULL;
	}
	printf("exit\n");
	return (0);
}
