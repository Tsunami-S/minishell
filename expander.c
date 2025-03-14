/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:21:12 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/14 17:00:22 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*head;
	t_tokens	*tmp;

	head = *tokens;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

static char	*concat_tokens(t_tokens **tokens)
{
	size_t		malloc_size;
	t_tokens	*head;
	char		*ans;

	malloc_size = 0;
	head = *tokens;
	while (head)
	{
		malloc_size += ft_strlen(head->token) + 1;
		head = head->next;
	}
	ans = (char *)malloc(sizeof(char) * (malloc_size + 1));
	if (!ans)
		return (NULL);
	ans[0] = '\0';
	head = *tokens;
	while (head)
	{
		ft_strlcat(ans, head->token, malloc_size + 1);
		head = head->next;
		if (head)
			ft_strlcat(ans, " ", malloc_size + 1);
	}
	return (ans);
}

char	*expander(char *str, t_var **varlist)
{
	t_tokens	*tokens;
	char		*ans;

	tokens = NULL;
	tokens = tokenizer(str);
	if (!tokens)
		return (NULL);
	replace_vars(&tokens, varlist);
	if (!tokens)
		return (NULL);
	ans = concat_tokens(&tokens);
	free_tokens(&tokens);
	return (ans);
}
