/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:21:12 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/19 00:22:40 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*expander(char *str, t_var **varlist)
{
	t_tokens	*tokens;
	t_tokens	*tmp;

	tokens = NULL;
	tokens = pre_tokenizer(str);
	if (!tokens)
		return (NULL);
	if (replace_vars(&tokens, varlist) == ERROR)
	{
		free_tokens(&tokens);
		return (NULL);
	}
	while (tokens && !tokens->token[0])
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->token);
		free(tmp);
	}
	more_tokenizer(&tokens);
	return (tokens);
}
