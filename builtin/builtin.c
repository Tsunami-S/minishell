/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:04:12 by haito             #+#    #+#             */
/*   Updated: 2025/03/23 12:01:08 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
	{
		perror("minishell: pwd:");
		return (1);
	}
	return (0);
}

int	child_call_builtin(t_tokens **tokens, t_var **varlist, t_status *st_head)
{
	t_tokens	*token;
	t_saved		saved;
	int			status;

	token = *tokens;
	status = redirect_builtin(tokens, &saved, varlist);
	if (status != EXIT_FAILURE)
	{
		if (ft_strcmp(token->token, "echo") == 0)
			status = builtin_echo(tokens, varlist);
		if (ft_strcmp(token->token, "cd") == 0)
			status = builtin_cd(tokens, varlist);
		if (ft_strcmp(token->token, "pwd") == 0)
			status = builtin_pwd();
		if (ft_strcmp(token->token, "export") == 0)
			status = builtin_export(tokens, varlist, 0);
		if (ft_strcmp(token->token, "unset") == 0)
			status = builtin_unset(tokens, varlist);
		if (ft_strcmp(token->token, "env") == 0)
			status = builtin_env(tokens, varlist);
		if (ft_strcmp(token->token, "exit") == 0)
			status = builtin_exit(tokens, varlist, st_head);
	}
	builtin_reset_stdio(&saved);
	free_varlist(varlist);
	free_tokens(tokens);
	return (status);
}

int	check_status(int status, t_tokens **tokens, t_var **varlist)
{
	t_tokens	*head;
	char		*new_value;
	char		*name;

	if (status != EXIT_SUCCESS)
		return (status);
	head = *tokens;
	while (head && head->next)
		head = head->next;
	new_value = ft_strdup(head->token);
	if (!new_value)
		return (status);
	name = ft_strdup("_");
	if (!name)
		return (free(new_value), status);
	add_var(varlist, name, new_value);
	return (status);
}

int	call_builtin(t_tokens **tokens, t_var **varlist, t_status *st_head)
{
	t_tokens	*token;
	t_saved		saved;
	int			status;

	token = *tokens;
	status = redirect_builtin(tokens, &saved, varlist);
	if (status != EXIT_FAILURE)
	{
		if (ft_strcmp(token->token, "echo") == 0)
			status = builtin_echo(tokens, varlist);
		if (ft_strcmp(token->token, "cd") == 0)
			status = builtin_cd(tokens, varlist);
		if (ft_strcmp(token->token, "pwd") == 0)
			status = builtin_pwd();
		if (ft_strcmp(token->token, "export") == 0)
			status = builtin_export(tokens, varlist, 0);
		if (ft_strcmp(token->token, "unset") == 0)
			status = builtin_unset(tokens, varlist);
		if (ft_strcmp(token->token, "env") == 0)
			status = builtin_env(tokens, varlist);
		if (ft_strcmp(token->token, "exit") == 0)
			status = builtin_exit(tokens, varlist, st_head);
	}
	builtin_reset_stdio(&saved);
	return (check_status(status, tokens, varlist));
}
