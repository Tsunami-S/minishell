/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:04:12 by haito             #+#    #+#             */
/*   Updated: 2025/03/31 11:50:35 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_var **varlist)
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
		cwd = get_path(varlist, "PWD");
		if (cwd)
			printf("%s\n", cwd);
		else
		{
			perror("minishell: pwd");
			return (1);
		}
	}
	return (0);
}

int	child_call_builtin(t_tokens **tokens, t_var **varlist, char *tmpfile)
{
	t_tokens	*token;
	t_saved		saved;
	int			status;

	status = redirect_builtin(tokens, &saved, tmpfile);
	if (status != EXIT_FAILURE)
	{
		token = delete_redirect(tokens);
		if (ft_strcmp(token->token, "echo") == 0)
			status = builtin_echo(&token, varlist);
		if (ft_strcmp(token->token, "cd") == 0)
			status = builtin_cd(&token, varlist);
		if (ft_strcmp(token->token, "pwd") == 0)
			status = builtin_pwd(varlist);
		if (ft_strcmp(token->token, "export") == 0)
			status = builtin_export(&token, varlist, 0);
		if (ft_strcmp(token->token, "unset") == 0)
			status = builtin_unset(&token, varlist);
		if (ft_strcmp(token->token, "env") == 0)
			status = builtin_env(&token, varlist);
		if (ft_strcmp(token->token, "exit") == 0)
			status = builtin_exit_child(&token, varlist);
	}
	builtin_reset_stdio(&saved);
	return (free_varlist(varlist), free_tokens(tokens), free(tmpfile), status);
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

int	call_builtin_re(t_tokens **tokens, t_var **varlist, t_status *st_head,
		t_lp *lp)
{
	t_tokens	*token;
	t_saved		saved;
	int			status;

	status = redirect_builtin(tokens, &saved, lp->heredoc_tmp);
	if (status != EXIT_FAILURE)
	{
		token = delete_redirect(tokens);
		if (ft_strcmp(token->token, "echo") == 0)
			status = builtin_echo(&token, varlist);
		if (ft_strcmp(token->token, "cd") == 0)
			status = builtin_cd(&token, varlist);
		if (ft_strcmp(token->token, "pwd") == 0)
			status = builtin_pwd(varlist);
		if (ft_strcmp(token->token, "export") == 0)
			status = builtin_export(&token, varlist, 0);
		if (ft_strcmp(token->token, "unset") == 0)
			status = builtin_unset(&token, varlist);
		if (ft_strcmp(token->token, "env") == 0)
			status = builtin_env(&token, varlist);
		if (ft_strcmp(token->token, "exit") == 0)
			status = builtin_exit_re(&token, varlist, st_head, lp);
	}
	builtin_reset_stdio(&saved);
	return (status);
}

int	call_builtin(t_tokens **tokens, t_var **varlist, t_status *st_head,
		char *tmpfile)
{
	t_tokens	*token;
	t_saved		saved;
	int			status;

	status = redirect_builtin(tokens, &saved, tmpfile);
	if (status != EXIT_FAILURE)
	{
		token = delete_redirect(tokens);
		if (ft_strcmp(token->token, "echo") == 0)
			status = builtin_echo(&token, varlist);
		if (ft_strcmp(token->token, "cd") == 0)
			status = builtin_cd(&token, varlist);
		if (ft_strcmp(token->token, "pwd") == 0)
			status = builtin_pwd(varlist);
		if (ft_strcmp(token->token, "export") == 0)
			status = builtin_export(&token, varlist, 0);
		if (ft_strcmp(token->token, "unset") == 0)
			status = builtin_unset(&token, varlist);
		if (ft_strcmp(token->token, "env") == 0)
			status = builtin_env(&token, varlist);
		if (ft_strcmp(token->token, "exit") == 0)
			status = builtin_exit(&token, varlist, st_head);
	}
	builtin_reset_stdio(&saved);
	return (check_status(status, tokens, varlist));
}
