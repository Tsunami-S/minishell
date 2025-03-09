/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:09:16 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/10 00:04:45 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isdigit_words(char *str, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	isredirect(char c)
{
	return (c == '<' || c == '>');
}

static void	make_new_token(char *str, int len, t_tokens **tokens)
{
	t_tokens	*new_token;
	t_tokens	*prev_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_token)
		return ;
	new_token->token = ft_strndup(str, len);
	if (!new_token->token)
		return ;
	if (str[len - 1] == '<' || str[len - 1] == '>')
		new_token->kind = REDIRECT;
	else
		new_token->kind = WORD;
	new_token->next = NULL;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		prev_token = *tokens;
		while (prev_token->next)
			prev_token = prev_token->next;
		prev_token->next = new_token;
	}
}

t_tokens	*tokenizer(char *str)
{
	t_tokens	*tokens;
	char		*start;
	int			si;
	int			ei;

	tokens = NULL;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		start = str;
		while (*str && !ft_isspace(*str) && !isredirect(*str))
			str++;
		if (*str && isredirect(*str) && isdigit_words(start, str - start))
			while (*str && isredirect(*str))
				str++;
		make_new_token(start, str - start, &tokens);
	}
	return (tokens);
}
