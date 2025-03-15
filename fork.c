/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:21:03 by haito             #+#    #+#             */
/*   Updated: 2025/03/15 21:54:35 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_builtin(void)
{
	printf("builtin\n");
	return (0);
}

void	update_exit_code(int exit_code, t_var **varlist)
{
	(void)exit_code;
	(void)varlist;
}

void	fork_and_wait(t_status **st_head, t_var **varlist)
{
	t_status	*st;
	//t_status	*st_previous;
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
				continue_child(&st->token, varlist);
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
	update_exit_code(exit_code, varlist);
}
