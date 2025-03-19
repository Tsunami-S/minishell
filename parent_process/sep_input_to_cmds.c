/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_input_to_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hito <hito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:54:32 by haito             #+#    #+#             */
/*   Updated: 2025/03/19 13:57:09 by hito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(const char *input, int i)
{
	if (i == ERROR)
		return (ERROR);
	while (input[i] == ' ')
		i++;
	i--;
	return (i);
}

int	handle_quotes(const char *input, char **cmds, int i)
{
	char	quote;

	quote = input[i];
	*cmds = add_char(*cmds, input[i++], &i);
	if (!*cmds)
		return (ERROR);
	while (input[i] && input[i] != quote)
		*cmds = add_char(*cmds, input[i++], &i);
	if (!*cmds)
		return (ERROR);
	*cmds = add_char(*cmds, input[i], &i);
	if (!*cmds)
		return (ERROR);
	return (i);
}

int	handle_brackets(const char *input, t_brackets *brackets,
	t_status **st_head, t_parser *ps)
{
	int			pair;
	t_status	*new_node;

	if (ps->cmds)
		return (error_handle_brackets(ERRNO_ONE));
	pair = get_brackets_pair(ps->i, brackets);
	if (pair - ps->i <= 1)
		return (error_handle_brackets(ERRNO_TWO));
	ps->cmds = trim_spaces(ft_substr(input, ps->i + 1, pair - ps->i - 1));
	if (!ps->cmds)
		return (error_handle_brackets(ERRNO_THREE));
	new_node = ft_new_node(ps->cmds, 1);
	if (!new_node)
		return (error_handle_brackets(ERRNO_THREE));
	ft_add_back_node(st_head, new_node);
	free(ps->cmds);
	ps->cmds = NULL;
	ps->i = pair;
	while (input[ps->i + 1] && input[ps->i + 1] == ' ')
		ps->i++;
	if ((input[ps->i + 1] != '\0' && input[ps->i + 1] != '|'
			&& input[ps->i + 1] != '&')
		|| (input[ps->i + 1] == '&' && input[ps->i + 2] != '&'))
		return (error_handle_brackets(ERRNO_FOUR));
	return (ps->i);
}

int	handle_operator(char *op, const char *input,
	t_status **st_head, t_parser *ps)
{
	ps->i = add_operator_node(op, &ps->cmds, st_head, ps->i);
	return (skip_spaces(input, ps->i));
}

t_status	*sep_input_to_cmds(const char *input, t_brackets *brackets,
		t_status *st_head)
{
	t_parser	ps;

	ps.i = -1;
	ps.cmds = NULL;
	while (input[++ps.i])
	{
		if (input[ps.i] == '\'' || input[ps.i] == '\"')
			ps.i = handle_quotes(input, &ps.cmds, ps.i);
		else if (input[ps.i] == '(')
			ps.i = handle_brackets(input, brackets, &st_head, &ps);
		else if (input[ps.i] == '|' && input[ps.i + 1] == '|')
			ps.i = handle_operator("||", input, &st_head, &ps);
		else if (input[ps.i] == '&' && input[ps.i + 1] == '&')
			ps.i = handle_operator("&&", input, &st_head, &ps);
		else if (input[ps.i] == '|')
			ps.i = handle_operator("|", input, &st_head, &ps);
		else
			ps.cmds = add_char(ps.cmds, input[ps.i], &ps.i);
		if (ps.i == ERROR)
			return (free_lst_status(st_head, NULL), NULL);
	}
	if (add_command_node(&ps.cmds, &st_head) == ERROR)
		return (free_lst_status(st_head, NULL), NULL);
	return (st_head);
}
