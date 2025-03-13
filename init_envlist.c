/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:21:12 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/13 23:36:44 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_set(char *envp, char **var_name, char **var_value)
{
	int	name_size;

	name_size = 0;
	while (envp[name_size] != '=')
		name_size++;
	*var_name = (char *)malloc(sizeof(char) * (name_size + 1));
	if (!*var_name)
		return ;
	ft_strlcpy(*var_name, envp, name_size + 1);
	*var_value = ft_strdup(&envp[name_size + 1]);
	if (!*var_value)
		return ;
}

t_var	*init_envp(char **envp)
{
	t_var	*varlist;
	int		var_size;
	char	*var_name;
	char	*var_value;

	if (!envp)
		return (NULL);
	varlist = NULL;
	var_size = 0;
	while (envp[var_size])
	{
		var_set(envp[var_size], &var_name, &var_value);
		add_var(&varlist, var_name, var_value);
		var_size++;
	}
	return (varlist);
}
