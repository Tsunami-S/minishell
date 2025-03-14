/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 07:48:56 by haito             #+#    #+#             */
/*   Updated: 2025/03/15 02:06:43 by haito            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	is_operator(const char *cmds)
{
	if (!ft_strcmp(cmds, "||") || !ft_strcmp(cmds, "&&")
		|| !ft_strcmp(cmds, "|"))
		return (1);
	return (0);
}

void	make_pipe(t_status **st_head)
{
	t_status	*st;
	t_status	*st_next;
	t_status	*remove_node;
	int			pipefd[2];

	if (!st_head || !*st_head)
		return ;
	st = *st_head;
	if (is_operator(st->cmds))
	{
		printf("syntax error head ope\n");
		return ;
	}
	while (st)
	{
		if (!is_operator(st->cmds))
		{
			st_next = st->next;
			if (!st_next)
				break ;
			else if (!ft_strcmp(st_next->cmds, "||"))
			{
				st_next = st_next->next;
				st_next->has_or = 1;
				ft_remove_node(st_head, st_next->previous);
			}
			else if (!ft_strcmp(st_next->cmds, "&&"))
			{
				st_next = st_next->next;
				st_next->has_and = 1;
				ft_remove_node(st_head, st_next->previous);
			}
			else if (!ft_strcmp(st_next->cmds, "|"))
			{
				if (!st_next->next)
				{
					printf("syntax error: unexpected end of command\n");
					return ;

				}
				if (pipe(pipefd) == -1)
				{
					perror("pipe error");
					return ;

				}
				st->output_pipefd = pipefd[1];
				st_next = st_next->next;
				st_next->input_pipefd = pipefd[0];
				remove_node = st_next->previous;
				ft_remove_node(st_head, remove_node);
			}
			st = st->next;
		}
		else
		{
			printf("has operator in a row");
			return ;

		}
	}
}
