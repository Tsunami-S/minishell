/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 07:48:56 by haito             #+#    #+#             */
/*   Updated: 2025/03/16 14:17:51 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(const char *cmds)
{
	if (!ft_strcmp(cmds, "||") || !ft_strcmp(cmds, "&&")
		|| !ft_strcmp(cmds, "|"))
		return (1);
	return (0);
}

int	process_and_or_operator(t_status **st_head, t_status *st_next, int ope)
{
	if (!st_next->next)
		return (error_pipe(ERRNO_TWO));
	st_next = st_next->next;
	if (ope == IS_OR)
		st_next->has_or = 1;
	if (ope == IS_AND)
		st_next->has_and = 1;
	ft_remove_node(st_head, st_next->previous);
	return (SUCCESS);
}

int	process_pipe_operator(t_status **st_head, t_status *st, t_status *st_next)
{
	int	pipefd[2];

	if (!st_next->next)
		return (error_pipe(ERRNO_TWO));
	if (pipe(pipefd) == -1)
		return (error_pipe(ERRNO_THREE));
	st->output_pipefd = pipefd[1];
	st_next = st_next->next;
	st_next->input_pipefd = pipefd[0];
	ft_remove_node(st_head, st_next->previous);
	return (SUCCESS);
}

int	process_operator(t_status **st_head, t_status *st)
{
	t_status	*st_next;

	st_next = st->next;
	if (!st_next)
		return (SUCCESS);
	else if (!ft_strcmp(st_next->cmds, "||"))
		return (process_and_or_operator(st_head, st_next, IS_OR));
	else if (!ft_strcmp(st_next->cmds, "&&"))
		return (process_and_or_operator(st_head, st_next, IS_AND));
	else if (!ft_strcmp(st_next->cmds, "|"))
		return (process_pipe_operator(st_head, st, st_next));
	return (SUCCESS);
}

int	make_pipe(t_status **st_head)
{
	t_status	*st;

	if (!st_head || !*st_head)
		return (ERROR);
	st = *st_head;
	if (is_operator(st->cmds))
		return (error_pipe(ERRNO_ONE));
	while (st)
	{
		if (!is_operator(st->cmds))
		{
			if (process_operator(st_head, st) == ERROR)
				return (ERROR);
		}
		else
			return (error_pipe(ERRNO_FOUR));
		st = st->next;
	}
	return (SUCCESS);
}
