/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:30:29 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/18 21:23:58 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*make_new_token(char *str, t_tokens *prev, t_tokens *next)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->token = ft_strdup(str);
	if (!new->token)
	{
		free(new);
		return (NULL);
	}
	prev->next = new;
	new->next = next;
	new->type = WORD;
	return (new);
}

int	more_tokenizer(t_tokens **tokens)
{
	t_tokens	*head;
	t_tokens	*new;
	int			i;
	int			j;

	head = *tokens;
	while (head)
	{
		i = 0;
		while (head->token[i] && !ft_isspace(head->token[i])
			&& head->token[i] != '=')
			i++;
		j = 0;
		while (ft_isspace(head->token[i + j]))
			j++;
		if (head->token[i + j] && head->token[i] != '=')
		{
			new = make_new_token(&head->token[i + j], head, head->next);
			if (!new)
				return (ERROR);
			head->token[i] = '\0';
		}
		head = head->next;
	}
	return (SUCCESS);
}
