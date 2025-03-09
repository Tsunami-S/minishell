/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:21:12 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/10 00:10:51 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_var(t_var *var)
{
	free(var->name);
	free(var->value);
	free(var);
}

t_var	*get_var(t_var **varlist, char *name)
{
	t_var	*tmp_var;

	if (!varlist || !*varlist)
		return (NULL);
	tmp_var = *varlist;
	while (tmp_var && ft_strcmp(tmp_var->name, name))
		tmp_var = tmp_var->next;
	return (tmp_var);
}

void	add_var(t_var **varlist, char *var_name, char *var_value)
{
	t_var	*new;
	t_var	*backward_var;

	if (!varlist)
		return ;
	new = get_var(varlist, var_name);
	if (new)
	{
		free(new->value);
		new->value = var_value;
		free(var_name);
		return ;
	}
	new = (t_var *)malloc(sizeof(t_var));
	if (!new)
		return ;
	// exit malloc error
	new->name = var_name;
	new->value = var_value;
	new->next = NULL;
	if (!*varlist)
	{
		*varlist = new;
		return ;
	}
	backward_var = *varlist;
	while (backward_var->next)
		backward_var = backward_var->next;
	backward_var->next = new;
}

t_var	**remove_var(t_var **varlist, char *name)
{
	t_var	**first_var;
	t_var	*tmp_var;

	if (!varlist && !*varlist)
		return (NULL);
	if (!ft_strcmp((*varlist)->name, name))
	{
		first_var = &(*varlist)->next;
		//	free_var(*varlist);
		return (first_var);
	}
	first_var = varlist;
	tmp_var = *varlist;
	while (tmp_var->next && ft_strcmp(tmp_var->next->name, name))
		tmp_var = tmp_var->next;
	if (!tmp_var->next)
		return (first_var);
	// tmp = (*varlist)->next;
	tmp_var->next = tmp_var->next->next;
	// free_var(tmp);
	return (first_var);
}

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
