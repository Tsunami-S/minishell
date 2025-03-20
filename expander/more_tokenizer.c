/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:30:29 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/20 17:23:20 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quotes(char **words)
{
	int		i;
	char	ope;
	char	*str;

	str = *words;
	i = 0;
	while (1)
	{
		i = 0;
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			i++;
		if (!str[i])
			break ;
		ope = str[i];
		ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
		while (str[i] && str[i] != ope)
			i++;
		ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
	}
}

static t_tokens	*add_new_tokens(t_tokens **prev, char **words)
{
	t_tokens	*new;
	t_tokens	*token_prev;
	int			i;

	token_prev = *prev;
	free(token_prev->token);
	token_prev->token = words[0];
	i = 1;
	while (words[i])
	{
		new = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new)
			return (NULL);
		new->type = WORD;
		new->token = words[i];
		new->next = token_prev->next;
		token_prev->next = new;
		token_prev = new;
		i++;
	}
	return (new);
}

int	more_tokenizer(t_tokens **tokens, t_type flag)
{
	t_tokens	*head;
	char		**words;
	int			i;

	head = *tokens;
	while (head)
	{
		words = split_words(head->token, flag);
		if (!words)
			return (ERROR);
		i = 0;
		while (words[i])
			remove_quotes(&words[i++]);
		if (i == 1)
		{
			free(head->token);
			head->token = words[0];
		}
		else
			head = add_new_tokens(&head, words);
		free(words[i]);
		free(words);
		if (i != 1 && !head)
			return (ERROR);
		head = head->next;
	}
	return (SUCCESS);
}
