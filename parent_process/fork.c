/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:21:03 by haito             #+#    #+#             */
/*   Updated: 2025/03/16 19:27:18 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_exit_code(int exit_code, t_var **varlist)
{
	t_var	*var;

	if (!varlist || !*varlist)
		return (ft_eprintf("minishell: not found exit status\n"), ERROR);
	var = *varlist;
	while (var && ft_strcmp(var->name, "?") != 0)
		var = var->next;
	if (!var)
		return (ft_eprintf("minishell: not found exit status\n"), ERROR);
	free(var->value);
	var->value = ft_itoa(exit_code);
	if (!var->value)
		return (error_node(ERRNO_ONE));
	return (SUCCESS);
}

int	wait_process(t_lp *lp, t_var **varlist, t_status **st_head)
{
	t_status	*st;
	int			status;
	int			exit_code;
	int			wait_count;

	st = *st_head;
	wait_count = 0;
	if (lp->count_forked != 0)
	{
		waitpid(lp->last_pid, &status, 0);
		exit_code = WEXITSTATUS(status);
	}
	else
		exit_code = lp->result;
	while (st && wait_count < lp->count_forked)
	{
		if (st->pid > 0)
		{
			waitpid(st->pid, NULL, 0);
			wait_count++;
		}
		st = st->next;
	}
	return (update_exit_code(exit_code, varlist));
}

void	fork_process(t_status *st, t_var **varlist,
		int *result, int *count_forked)
{
	st->pid = fork();
	if (st->pid == -1)
	{
		perror("minishell: fork: ");
		*result = FAILED;
		return ;
	}
	(*count_forked)++;
	if (st->pid == 0)
		handle_child_process(st, varlist);
	handle_parent_process(st);
	handle_and_or(st, result);
}

int	fork_and_wait(t_status **st_head, t_var **varlist)
{
	t_status	*st;
	t_lp		lp;

	st = *st_head;
	lp.count_forked = 0;
	lp.last_pid = -1;
	lp.result = 0;
	while (st)
	{
		if ((st->has_and && lp.result != 0) || (st->has_or && lp.result == 0))
			;
		else if (st->is_builtin && (!st->next || st->next->has_and
				|| st->next->has_or) && st->has_brackets == 0)
			lp.result = call_builtin(&st->token, varlist);
		else
		{
			fork_process(st, varlist, &lp.result, &lp.count_forked);
			if (!st->next || (!st->next->has_and && !st->next->has_or))
				lp.last_pid = st->pid;
		}
		st = st->next;
	}
	return (wait_process(&lp, varlist, st_head));
}
