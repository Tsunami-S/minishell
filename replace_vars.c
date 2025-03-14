/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:41:50 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/14 16:59:31 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_words(char **words, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (words[i])
			free(words[i]);
		i++;
	}
	free(words);
}

static char	*concat_words(char **words, int size)
{
	char	*expanded_token;
	size_t	total_len;
	int		i;

	total_len = 0;
	i = 0;
	while (i < size)
	{
		total_len += ft_strlen(words[i]);
		i++;
	}
	expanded_token = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!expanded_token)
		return NULL;
	expanded_token[0] = '\0';
	i = 0;
	while (i < size)
	{
		if (words[i])
			ft_strlcat(expanded_token, words[i], total_len + 1);
		i++;
	}
	free_words(words, size);
	return (expanded_token);
}

void	replace_vars(t_tokens **tokens, t_var **varlist)
{
	t_tokens	*head;
	char		**words;
	int			words_size;

	head = *tokens;
	while (head)
	{
		if (head->kind == WORD)
		{
			words_size = count_words_and_vars(head->token);
			words = split_token(head->token, words_size, varlist);
			if(!words)
			{
				free_tokens(tokens);
				return;
			}
			free(head->token);
			head->token = NULL;
			head->token = concat_words(words, words_size);
			if(!head->token)
			{
				free_tokens(tokens);
				return;
			}
		}
		head = head->next;
	}
}
