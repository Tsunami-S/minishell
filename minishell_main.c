/*************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:11:19 by haito             #+#    #+#             */
/*   Updated: 2025/03/15 13:41:46 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmds(t_status **st_head, t_var **varlist)
{
	t_status	*st;
	char		*expanded_cmds;

	if (!st_head || !*st_head)
		return ;
	st = *st_head;
	while (st)
	{
		st->token = expander(st->cmds, varlist);
		expanded_cmds = "";
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

	if (!input)
		return (0);
	if (find_brackets_pair(input, &brackets, ft_strlen(input)) == ERROR)
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_var	*varlist;

	if (argc != 1)
		return (1);
	(void)argv;
	varlist = init_varlist(envp);
	if (!varlist)
		return (1);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			return (0);
		}
		if (*input)
			add_history(input);
		continue_line(input, &varlist);
		free(input);
		input = NULL;
	}
	return (0);
}
