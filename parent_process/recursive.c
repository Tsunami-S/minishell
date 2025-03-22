/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:01:42 by haito             #+#    #+#             */
/*   Updated: 2025/03/22 22:08:11 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_process_(t_status *st, t_var **varlist,
	t_lp *lp, t_status *st_head)
{
	if (st->has_and_single)
		return ;
	st->pid = fork();
	if (st->pid == -1)
	{
		perror("minishell: fork: ");
		lp->result = FAILED;
		return ;
	}
	lp->count_forked++;
	if (st->pid == 0)
	{
		free(lp->input);
		handle_child_process(st, varlist, st_head);
	}
	handle_parent_process(st);
	handle_and_or(st, lp);
}

int	fork_and_wait_(t_status **st_head, t_var **varlist, char *input)
{
	t_status	*st;
	t_lp		lp;

	st = *st_head;
	lp.count_forked = 0;
	lp.last_pid = -1;
	lp.result = 0;
	lp.input = input;
	while (st)
	{
		if (g_signal == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			g_signal = 0;
			lp.result = 130;
			lp.count_forked = 0;
			break ;
		}
		if ((st->has_and && lp.result != 0) || (st->has_or && lp.result == 0))
			;
		else if (st->is_builtin && (!st->next || st->next->has_and
				|| st->next->has_or) && st->has_brackets == 0
			&& st->input_pipefd == -1 && st->output_pipefd == -1)
			lp.result = call_builtin(&st->token, varlist, *st_head);
		else
		{
			fork_process_(st, varlist, &lp, *st_head);
			if (!st->next || (!st->next->has_and && !st->next->has_or))
				lp.last_pid = st->pid;
		}
		st = st->next;
	}
	return (wait_process(&lp, varlist, st_head));
}

int	recursive_continue_line(char *input, t_var **varlist)
{
	t_status	*state;
	t_brackets	brackets;

	if (!input)
		return (0);
	if (find_brackets_pair(input, &brackets, ft_strlen(input),
			varlist) == ERROR)
		return (free_varlist(varlist), ERROR);
	state = sep_input_to_cmds(input, &brackets, NULL, varlist);
	if (!state)
		return (free_varlist(varlist), ERROR);
	if (make_pipe(&state, varlist) == ERROR)
		return (frees(state, varlist), ERROR);
	if (expand_cmds(&state, varlist) == ERROR)
		return (frees(state, varlist), ERROR);
	if (check_built_in(&state, state))
		return (frees(state, varlist), ERROR);
	if (fork_and_wait_(&state, varlist, input) == ERROR)
		return (frees(state, varlist), ERROR);
	frees(state, varlist);
	free(input);
	return (SUCCESS);
}
