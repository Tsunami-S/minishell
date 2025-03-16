/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:04:30 by haito             #+#    #+#             */
/*   Updated: 2025/03/16 17:46:49 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_tokens **tokens, t_var **varlist)
{
	(void)tokens;
	(void)varlist;
	printf("is export\n");
	return (0);
}

int	builtin_unset(t_tokens **tokens, t_var **varlist)
{
	(void)tokens;
	(void)varlist;
	printf("is unset\n");
	return (0);
}

int	builtin_env(t_tokens **tokens, t_var **varlist)
{
	(void)tokens;
	(void)varlist;
	printf("is env\n");
	return (0);
}
