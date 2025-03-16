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

int	expand_cmds(t_status **st_head, t_var **varlist)
{
	t_status	*st;

	if (!st_head || !*st_head)
		return (ERROR);
	st = *st_head;
	while (st)
	{
		st->token = expander(st->cmds, varlist);
		if (!st->token)
			return (ERROR);
		st = st->next;
	}
	return (SUCCESS);
}

int	check_built_in(t_status **st_head, t_status *st)
{
	char		**builtin_cmds;
	int			i;

	if (!st_head || !*st_head || !st)
		return (ERROR);
	builtin_cmds = init_builtin_cmds();
	if (!builtin_cmds)
		return (error_node(ERRNO_ONE), ERROR);
	while (st)
	{
		i = -1;
		while (builtin_cmds[++i])
		{
			if (!ft_strcmp(st->token->token, builtin_cmds[i]))
			{
				st->is_builtin = 1;
				break ;
			}
		}
		st = st->next;
	}
	free_builtin_cmds(builtin_cmds);
	return (SUCCESS);
}

int	recursive_continue_line(char *input, t_var **varlist)
{
	t_status	*state;
	t_brackets	brackets;

	(void)varlist;

	if (!input)
		return (0);
	if (find_brackets_pair(input, &brackets, ft_strlen(input)) == ERROR)
		return (free_varlist(varlist), ERROR);
	state = sep_input_to_cmds(input, &brackets, NULL);
	if (!state)
		return (free_varlist(varlist), ERROR);
	if (make_pipe(&state) == ERROR)
		return (frees(state, 1, varlist), ERROR);
	if (expand_cmds(&state, varlist) == ERROR)
		return (frees(state, 1, varlist), ERROR);
	if (check_built_in(&state, state))
		return (frees(state, 1, varlist), ERROR);
	if (fork_and_wait(&state, varlist) == ERROR)
		return (frees(state, 1, varlist), ERROR);
	frees(state, 1, varlist);
	return (SUCCESS);
}

int	continue_line(char *input, t_var **varlist)
{
	t_status	*state;
	t_brackets	brackets;

	(void)varlist;

	if (!input)
		return (0);
	if (find_brackets_pair(input, &brackets, ft_strlen(input)) == ERROR)
		return (ERROR);
	state = sep_input_to_cmds(input, &brackets, NULL);
	if (!state)
		return (ERROR);
	if (make_pipe(&state) == ERROR)
		return (free_lst_status(state, 1), ERROR);
	if (expand_cmds(&state, varlist) == ERROR)
		return (free_lst_status(state, 1), ERROR);
	if (check_built_in(&state, state))
		return (free_lst_status(state, 1), ERROR);
	if (fork_and_wait(&state, varlist) == ERROR)
		return (free_lst_status(state, 1), ERROR);
	free_lst_status(state, 1);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_var	*varlist;

	if (argc != 1)
		return (ft_eprintf("minishell: too many argument\n"), FAILED);
	(void)argv;
	varlist = init_varlist(envp, ft_strdup("?"), ft_strdup("0"));
	if (!varlist)
		return (FAILED);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			return (free_varlist(&varlist), 0);
		}
		if (*input)
			add_history(input);
		continue_line(input, &varlist);
		free(input);
		input = NULL;
	}
	return (free_varlist(&varlist), 0);
}
