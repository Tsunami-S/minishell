/*************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:11:19 by haito             #+#    #+#             */
/*   Updated: 2025/03/14 13:29:54 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_builtin(void)
{
	printf("builtin\n");
	return (0);
}

void	continue_child(void)
{
	char **cmd;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = malloc(3);
	cmd[0][0] = 'l';
	cmd[0][1] = 's';
	cmd[0][2] = '\0';
	cmd[1] = NULL;
	execve("/usr/bin/ls", cmd, NULL);
	exit(1);
}

void	fork_and_wait(t_status **st_head, t_var **varlist)
{
	t_status	*st;
	t_status	*st_previous;
	pid_t		last_pid;
	int			result;
	int			count_forked;
	int			status;
	int			exit_code;

	st = *st_head;
	count_forked = 0;
	last_pid = -1;
	while (st)
	{
		if (st->is_builtin && (!st->next || st->next->has_and
				|| st->next->has_or))
		{
			result = call_builtin();
			if ((st->next && st->next->has_and && result != 0)
				|| (st->next && st->next->has_or && result == 0))
				break ;
		}
		else
		{
			st->pid = fork();
			if (st->pid == -1)
				error_process();
			count_forked++;
			if (st->pid == 0)
			{
				if (st->input_pipefd != -1)
					dup2(st->input_pipefd, STDIN_FILENO);
				if (st->output_pipefd != -1)
					dup2(st->output_pipefd, STDOUT_FILENO);
				if (st->has_brackets)
				{
					if (continue_line(st->cmds, varlist) == -1)
						error_process();
					exit(0);
				}
				//countinue_child(st->token, varlist);
				continue_child();
			}
			if (st->next && st->next->has_and)
			{
				waitpid(st->pid, &status, 0);
				if (WEXITSTATUS(status) != 0)
					break ;
			}
			if (st->next && st->next->has_or)
			{
				waitpid(st->pid, &status, 0);
				if (WEXITSTATUS(status) == 0)
					break ;
			}
			else
				last_pid = st->pid;
		}
		st = st->next;
	}
	waitpid(last_pid, &status, 0);
	exit_code = WEXITSTATUS(status);
	while (count_forked-- > 1)
		wait(NULL);
}

void	expand_cmds(t_status **st_head, t_var **varlist)
{
	t_status	*st;
	char		*expanded_cmds;

	if (!st_head || !*st_head)
		return ;
	st = *st_head;
	while (st)
	{
		expanded_cmds = expander(st->cmds, varlist);
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

int	continue_line(char *input, t_var **varlist)
{
	t_status	*state;
	t_brackets	brackets;


	if (find_brackets_pair(input, &brackets) == -1)
		return (1);
	state = sep_input_to_cmds(input, &brackets);
	make_pipe(&state);
	expand_cmds(&state, varlist);
	check_built_in(&state, state);
	t_status *st = state;
	while (st != NULL)
	{
		printf("cmd:%s in:%d out:%d ():%d or:%d and:%d built:%d\n", st->cmds, st->input_pipefd, st->output_pipefd, st->has_brackets, st->has_or, st->has_and, st->is_builtin);
		st = st->next;
	}
	fork_and_wait(&state, varlist);
	return (0);
}

void	process_line(char *input, t_var **varlist)
{
	// pid_t	pid;
	// int		status;

	// pid = fork();
	// if (pid == -1)
	// 	error_process();
	// if (pid == 0)
	continue_line(input, varlist);
	// waitpid(pid, &status, 0);
	// *exit_status = WEXITSTATUS(status);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_var *varlist;

	if (argc != 1)
		return (1);
	(void)argv;
	varlist = init_varlist(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (0);
		if (*input)
			add_history(input);
		process_line(input, &varlist);
		free(input);
		input = NULL;
	}
	printf("exit\n");
	return (0);
}
