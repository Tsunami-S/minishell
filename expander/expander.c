/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:21:12 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/15 19:53:04 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*expander(char *str, t_var **varlist)
{
	t_tokens	*tokens;

	tokens = NULL;
	tokens = tokenizer(str);
	if (!tokens)
		return (NULL);
	replace_vars(&tokens, varlist);
	if (!tokens)
		return (NULL);
	return (tokens);
}
