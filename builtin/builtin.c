/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:04:12 by haito             #+#    #+#             */
/*   Updated: 2025/03/16 20:15:59 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_tokens **tokens, t_var **varlist)
{
	(void)tokens;
	(void)varlist;
	printf("is exit\n");
	return (0);
}

int	builtin_pwd(t_tokens **tokens, t_var **varlist)
{
	(void)tokens;
	(void)varlist;
	printf("is pwd\n");
	return (0);
}

int	builtin_cd(t_tokens **tokens, t_var **varlist)
{
	(void)tokens;
	(void)varlist;
	printf("is cd\n");
	return (0);
}

int	builtin_echo(t_tokens **tokens, t_var **varlist)
{
	(void)tokens;
	(void)varlist;
	printf("is echo\n");
	return (0);
}

int	child_call_builtin(t_tokens **tokens, t_var **varlist)
{
	t_tokens	*token;
	t_saved saved;
	int status;

	token = *tokens;
	if (redirect_builtin(tokens, &saved))
		return (ERROR);
	if (ft_strcmp(token->token, "echo") == 0)
		status = builtin_echo(tokens, varlist);
	if (ft_strcmp(token->token, "cd") == 0)
		status = builtin_cd(tokens, varlist);
	if (ft_strcmp(token->token, "pwd") == 0)
		status = builtin_pwd(tokens, varlist);
	if (ft_strcmp(token->token, "export") == 0)
		status = builtin_export(tokens, varlist);
	if (ft_strcmp(token->token, "unset") == 0)
		status = builtin_unset(tokens, varlist);
	if (ft_strcmp(token->token, "env") == 0)
		status = builtin_env(tokens, varlist);
	if (ft_strcmp(token->token, "exit") == 0)
		status = builtin_exit(tokens, varlist);
	builtin_reset_stdio(&saved);
	free_varlist(varlist);
	free_tokens(tokens);
	return status;
}

int	call_builtin(t_tokens **tokens, t_var **varlist)
{
	t_tokens	*token;
	t_saved saved;
	int status;

	token = *tokens;
	if(redirect_builtin(tokens, &saved))
		return (ERROR);
	if (ft_strcmp(token->token, "echo") == 0)
		status = builtin_echo(tokens, varlist);
	if (ft_strcmp(token->token, "cd") == 0)
		status = builtin_cd(tokens, varlist);
	if (ft_strcmp(token->token, "pwd") == 0)
		status = builtin_pwd(tokens, varlist);
	if (ft_strcmp(token->token, "export") == 0)
		status = builtin_export(tokens, varlist);
	if (ft_strcmp(token->token, "unset") == 0)
		status = builtin_unset(tokens, varlist);
	if (ft_strcmp(token->token, "env") == 0)
		status = builtin_env(tokens, varlist);
	if (ft_strcmp(token->token, "exit") == 0)
		status = builtin_exit(tokens, varlist);
	builtin_reset_stdio(&saved);
	return status;
}
