/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_input_to_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:54:32 by haito             #+#    #+#             */
/*   Updated: 2025/03/13 10:56:44 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(const char *input, int i)
{
	while (input[i] == ' ')
		i++;
	i--;
	return (i);
}

int	handle_quotes(const char *input, char **cmds, int i)
{
	char	quote;

	quote = input[i];
	*cmds = add_char(*cmds, input[i++]);
	while (input[i] && input[i] != quote)
		*cmds = add_char(*cmds, input[i++]);
	*cmds = add_char(*cmds, input[i]);
	return (i);
}

int	handle_brackets(const char *input, t_brackets *brackets,
	t_status **st_head, t_parser *ps)
{
	int			pair;
	t_status	*new_node;

	if (ps->cmds)
		return (printf("syntax error\n"), exit(1), -1);
	pair = get_brackets_pair(ps->i, brackets);
	ps->cmds = trim_spaces(ft_substr(input, ps->i + 1, pair - ps->i - 1),
			-1, 0);
	new_node = ft_new_node(ps->cmds, 1);
	if (!new_node)
		error_process();
	ft_add_back_node(st_head, new_node);
	free(ps->cmds);
	ps->cmds = NULL;
	ps->i = pair;
	while (input[ps->i + 1] && input[ps->i + 1] == ' ')
		ps->i++;
	if ((input[ps->i + 1] != '\0' && input[ps->i + 1] != '|'
			&& input[ps->i + 1] != '&')
		|| (input[ps->i + 1] == '&' && input[ps->i + 2] != '&'))
		return (printf("syntax error\n"), exit(1), -1);
	return (ps->i);
}

int	handle_operator(const char *op, const char *input,
	t_status **st_head, t_parser *ps)
{
	ps->i = add_operator_node(op, &ps->cmds, st_head, ps->i);
	return (skip_spaces(input, ps->i));
}

t_status	*sep_input_to_cmds(const char *input, t_brackets *brackets)
{
	t_parser	ps;
	t_status	*st_head;

	ps.i = -1;
	ps.cmds = NULL;
	st_head = NULL;
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
			ps.cmds = add_char(ps.cmds, input[ps.i]);
	}
	add_command_node(&ps.cmds, &st_head);
	return (st_head);
}
