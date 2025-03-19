/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:21:12 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/19 16:30:17 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*remove_empty_top_tokens(t_tokens **tokens)
{
	t_tokens	*tmp;

	while (*tokens && !(*tokens)->token[0])
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->token);
		free(tmp);
	}
	return (*tokens);
}

static t_tokens	*remove_empty_tokens(t_tokens **tokens)
{
	t_tokens	*head;
	t_tokens	*prev;
	t_tokens	*tmp;

	prev = NULL;
	head = *tokens;
	while (head)
	{
		if (!head->token || !head->token[0])
		{
			tmp = head;
			prev->next = head->next;
			head = head->next;
			free(tmp->token);
			free(tmp);
		}
		else
		{
			prev = head;
			head = head->next;
		}
	}
	return (*tokens);
}

//static void check_first_token(t_tokens **tokens)
//{
//	t_tokens *head;
//	int i;
//
//	head = *tokens;
//	i = 0;
//	while(ft_isspace(head->token[i]))
//		i++;
//	if(head->token[i] == '$')
//	{
//		head = head->next;
//		while(head)
//		{
//			if(head->type == HAVE_QUOTE)
//				head->type = WORD;
//			head = head->next;
//		}
//	}
//}

t_tokens	*expander(char *str, t_var **varlist)
{
	t_tokens	*tokens;

	tokens = NULL;
	tokens = pre_tokenizer(str);
	if (!tokens)
		return (NULL);
	if (replace_vars(&tokens, varlist) == ERROR)
	{
		free_tokens(&tokens);
		return (NULL);
	}
	tokens = remove_empty_top_tokens(&tokens);
	tokens = remove_empty_tokens(&tokens);
	more_tokenizer(&tokens);
	return (tokens);
}
