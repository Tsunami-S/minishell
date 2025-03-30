/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:40:23 by haito             #+#    #+#             */
/*   Updated: 2025/03/30 20:50:14 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	delete_heredoc(t_status *st)
{
	while (st)
	{
		if (st->heredoc)
			unlink(st->heredoc);
		st = st->next;
	}
}

int	check_heredoc2(t_status *st, t_tokens *token, t_var **var)
{
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (!token->next)
				return (error_check_heredoc());
			if (st->heredoc)
			{
				unlink(st->heredoc);
				free(st->heredoc);
			}
			st->heredoc = here_doc(token->next->token, var);
			if (!st->heredoc)
				return (ERROR);
			if (token->next->next)
			{
				token = token->next->next;
				continue ;
			}
			else
				break ;
		}
		token = token->next;
	}
	return (0);
}

int	check_heredoc(t_status **st_head, t_var **var)
{
	t_status	*st;
	t_tokens	*token;
	int			heredoc_result;

	st = *st_head;
	while (st)
	{
		errno = 0;
		st->token = expander(st->cmds, var);
		if (!st->token)
		{
			if (errno)
				return (ERROR);
			return (0);
		}
		token = st->token;
		heredoc_result = check_heredoc2(st, token, var);
		if (heredoc_result == ERROR)
			return (ERROR);
		st = st->next;
	}
	return (0);
}

int	continue_line(char *input, t_var **varlist)
{
	t_status	*state;
	t_brackets	brackets;

	if (signal(SIGINT, sig_handler_inprocess) == SIG_ERR)
		return (perror("minishell: signal"), update_exit_code(1, varlist),
			ERROR);
	if (signal(SIGQUIT, sig_handler_inprocess) == SIG_ERR)
		return (perror("minishell: signal"), update_exit_code(1, varlist),
			ERROR);
	if (!input)
		return (0);
	if (find_brackets_pair(input, &brackets, ft_strlen(input),
			varlist) == ERROR)
		return (ERROR);
	state = sep_input_to_cmds(input, &brackets, NULL, varlist);
	if (!state)
		return (ERROR);
	if (make_pipe(&state, varlist) == ERROR)
		return (free_lst_status(state, NULL), ERROR);
	if (check_heredoc(&state, varlist) == ERROR)
		return (free_lst_status(state, NULL), ERROR);
	if (fork_and_wait(&state, varlist) == ERROR)
		return (free_lst_status(state, NULL), ERROR);
	delete_heredoc(state);
	return (free_lst_status(state, NULL), SUCCESS);
}

static void	setup_signal_handlers(t_var **varlist)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("minishell: signal");
		free_varlist(varlist);
		exit(1);
	}
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("minishell: signal");
		free_varlist(varlist);
		exit(1);
	}
}

void	main_loop(t_var **varlist)
{
	char	*input;
	int		result;

	while (1)
	{
		setup_signal_handlers(varlist);
		g_signal = 0;
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			result = get_exit_status(varlist);
			free_varlist(varlist);
			exit(result);
		}
		if (*input)
			add_history(input);
		continue_line(input, varlist);
		free(input);
		input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*varlist;

	if (argc != 1)
		return (ft_eprintf("minishell: too many argument\n"), FAILED);
	(void)argv;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (perror("minishell: signal"), 1);
	varlist = init_varlist(envp, ft_strdup("?"), ft_strdup("0"));
	if (!varlist)
		return (FAILED);
	count_up_shlvl(&varlist);
	main_loop(&varlist);
	return (free_varlist(&varlist), 0);
}
