/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hito <hito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:04:12 by haito             #+#    #+#             */
/*   Updated: 2025/03/19 15:25:40 by hito             ###   ########.fr       */
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

int	builtin_cd(t_tokens **tokens)
{
	t_tokens	*token;

	token = *tokens;
	if (token->next && token->next->next)
	{
		ft_eprintf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (token->next)
	{
		if (chdir(token->next->token) == -1)
		{
			perror("minishell: cd:");
			return (1);
		}
	}
	return (0);
}

int	child_call_builtin(t_tokens **tokens, t_var **varlist, t_status *st_head)
{
	t_tokens	*token;
	t_saved		saved;
	int			status;

	token = *tokens;
	if (redirect_builtin(tokens, &saved, varlist))
		return (ERROR);
	if (ft_strcmp(token->token, "echo") == 0)
		status = builtin_echo(tokens, varlist);
	if (ft_strcmp(token->token, "cd") == 0)
		status = builtin_cd(tokens);
	if (ft_strcmp(token->token, "pwd") == 0)
		status = builtin_pwd();
	if (ft_strcmp(token->token, "export") == 0)
		status = builtin_export(tokens, varlist);
	if (ft_strcmp(token->token, "unset") == 0)
		status = builtin_unset(tokens, varlist);
	if (ft_strcmp(token->token, "env") == 0)
		status = builtin_env(tokens, varlist);
	if (ft_strcmp(token->token, "exit") == 0)
		status = builtin_exit(tokens, varlist, st_head);
	builtin_reset_stdio(&saved);
	free_varlist(varlist);
	free_tokens(tokens);
	return (status);
}

int	call_builtin(t_tokens **tokens, t_var **varlist, t_status *st_head)
{
	t_tokens	*token;
	t_saved		saved;
	int			status;

	token = *tokens;
	if (redirect_builtin(tokens, &saved, varlist))
		return (ERROR);
	if (ft_strcmp(token->token, "echo") == 0)
		status = builtin_echo(tokens, varlist);
	if (ft_strcmp(token->token, "cd") == 0)
		status = builtin_cd(tokens);
	if (ft_strcmp(token->token, "pwd") == 0)
		status = builtin_pwd();
	if (ft_strcmp(token->token, "export") == 0)
		status = builtin_export(tokens, varlist);
	if (ft_strcmp(token->token, "unset") == 0)
		status = builtin_unset(tokens, varlist);
	if (ft_strcmp(token->token, "env") == 0)
		status = builtin_env(tokens, varlist);
	if (ft_strcmp(token->token, "exit") == 0)
		status = builtin_exit(tokens, varlist, st_head);
	builtin_reset_stdio(&saved);
	return (status);
}
