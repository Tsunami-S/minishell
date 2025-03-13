/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:09:13 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/13 23:37:07 by tssaito          ###   ########.fr       */
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
	new->name = var_name;
	new->value = var_value;
	new->next = NULL;
	if (!*varlist)
	{
		*varlist = new;
		return;
	}
	backward_var = *varlist;
	while (backward_var && backward_var->next)
		backward_var = backward_var->next;
	backward_var->next = new;
}

t_var	**remove_var(t_var **varlist, char *name)
{
	t_var	**first_var;
	t_var	*tmp_var;
	t_var	*remove_var;

	if (!varlist && !*varlist)
		return (NULL);
	if (!ft_strcmp((*varlist)->name, name))
	{
		first_var = &(*varlist)->next;
		return (first_var);
	}
	first_var = varlist;
	tmp_var = *varlist;
	while (tmp_var->next && ft_strcmp(tmp_var->next->name, name))
		tmp_var = tmp_var->next;
	if (!tmp_var->next)
		return (first_var);
	remove_var = tmp_var->next;
	tmp_var->next = tmp_var->next->next;
	free_var(remove_var);
	return (first_var);
}
