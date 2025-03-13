/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tunamis_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:21:12 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/13 23:48:08 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *concat_tokens(t_tokens *tokens)
{
	size_t malloc_size;
	t_tokens *head;
	char *ans;

	malloc_size = 0;
	head = tokens;
	while(head)
	{
		malloc_size += ft_strlen(head->token) + 1;
		head = head->next;
	}
	ans = (char *)malloc(sizeof(char) * (malloc_size + 1));
	if(!ans)
		return NULL;
	head = tokens;
	while(head)
	{
		ft_strlcat(ans, head->token, malloc_size + 1);
		head = head->next;
		if(head)
			ft_strlcat(ans, " ", malloc_size + 1);
		else
			break;
	}
	return ans;
}

char	*tunamis_expand(char *str, char **envp)
{
	t_tokens *tokens;
	t_var *varlist;
	char *ans;

	tokens = NULL;
	varlist = init_envp(envp);
	tokens = tokenizer(str);
	replace_envvar(&tokens, &varlist);
	ans = concat_tokens(tokens);
	return ans;
}
