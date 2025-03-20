/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:39:26 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/19 23:20:39 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (free_words(words, size), NULL);
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

t_tokens	*concat_words(t_tokens *head, char **words, int size)
{
}
