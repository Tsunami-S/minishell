/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:13:42 by hito              #+#    #+#             */
/*   Updated: 2025/03/22 22:09:45 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_var **varlist, char *path)
{
	t_var	*var;

	var = *varlist;
	while (var && ft_strcmp(var->name, path) != 0)
		var = var->next;
	if (!var)
		return (NULL);
	return (var->value);
}

int	update_pwd(t_var **varlist, char *cwd)
{
	char	*name_dup;
	char	*value_dup;

	name_dup = ft_strdup("PWD");
	if (!name_dup)
		return (free(cwd), error_node(ERRNO_ONE), FAILED);
	value_dup = ft_strdup(cwd);
	free(cwd);
	if (!value_dup)
		return (free(name_dup), error_node(ERRNO_ONE), FAILED);
	add_var(varlist, name_dup, value_dup);
	return (SUCCESS);
}

int	update_oldpwd(t_var **varlist)
{
	char	*oldpwd;
	char	*cwd;
	char	*name_dup;
	char	*value_dup;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell: cd"), FAILED);
	oldpwd = get_path(varlist, "PWD");
	name_dup = ft_strdup("OLDPWD");
	if (!name_dup)
		return (free(cwd), error_node(ERRNO_ONE), FAILED);
	if (!oldpwd)
	{
		add_var(varlist, name_dup, NULL);
		return (update_pwd(varlist, cwd));
	}
	value_dup = ft_strdup(oldpwd);
	if (!value_dup)
		return (free(name_dup), free(cwd), error_node(ERRNO_ONE), FAILED);
	add_var(varlist, name_dup, value_dup);
	return (update_pwd(varlist, cwd));
}

int	builtin_cd(t_tokens **tokens, t_var **varlist)
{
	t_tokens	*token;
	char		*dir;

	token = *tokens;
	if (token->next && token->next->next)
		return (ft_eprintf("minishell: cd: too many arguments\n"), FAILED);
	if (!token->next)
	{
		dir = get_path(varlist, "HOME");
		if (!dir)
			return (ft_eprintf("minishell: cd: HOME not set\n"), FAILED);
	}
	else if (ft_strcmp(token->next->token, "-") == 0)
	{
		dir = get_path(varlist, "OLDPWD");
		if (!dir)
			return (ft_eprintf("minishell: cd: OLDPWD not set\n"), FAILED);
		printf("%s\n", dir);
	}
	else
		dir = token->next->token;
	if (chdir(dir) == ERROR)
		return (perror("minishell: cd"), FAILED);
	return (update_oldpwd(varlist));
}
