/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:08:44 by haito             #+#    #+#             */
/*   Updated: 2025/03/16 18:15:17 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_and_or(t_status *st, int *result)
{
	int	status;

	if (st->next && (st->next->has_and || st->next->has_or))
	{
		waitpid(st->pid, &status, 0);
		*result = WEXITSTATUS(status);
	}
}

void	handle_parent_process(t_status *st)
{
	if (st->input_pipefd != -1)
		close(st->input_pipefd);
	if (st->output_pipefd != -1)
		close(st->output_pipefd);
}

void	handle_child_process(t_status *st, t_var **varlist)
{
	t_tokens	*token;

	if (st->input_pipefd != -1)
		dup2(st->input_pipefd, STDIN_FILENO);
	if (st->output_pipefd != -1)
		dup2(st->output_pipefd, STDOUT_FILENO);
	if (st->has_brackets)
		exit(recursive_continue_line(st->cmds, varlist));
	if (st->is_builtin)
	{
		token = st->token;
		free_lst_status(st, 2);
		exit(call_builtin(&token, varlist));
	}
	else
	{
		token = st->token;
		free_lst_status(st, 2);
		continue_child(&token, varlist);
	}
}
