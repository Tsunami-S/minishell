/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:41:50 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/13 23:47:06 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concat_words(char **words, int size)
{
	size_t	total_len;
	int		i;
	char	*final_token;

	total_len = 0;
	i = 0;
	while (i < size)
		total_len += ft_strlen(words[i++]);
	final_token = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!final_token)
		return (NULL);
	final_token[0] = '\0';
	i = 0;
	while (i < size)
	{
		if (words[i])
			ft_strlcat(final_token, words[i], total_len + 1);
		i++;
	}
	return (final_token);
}

void	replace_envvar(t_tokens **tokens, t_var **varlist)
{
	t_tokens	*head;
	char		**words;
	int			words_size;

	head = *tokens;
	while (head)
	{
		if(head->kind == WORD)
		{
			words_size = count_words_and_vars(head->token);
			words = split_to_words_and_vars(head->token, words_size, varlist);
			free(head->token);
			head->token = concat_words(words, words_size);
		}
		head = head->next;
	}
}
