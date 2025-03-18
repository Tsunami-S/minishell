/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:09:16 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/18 21:27:04 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_token_size(char *str)
{
	char	ope;

	if (*str == '<' || *str == '>')
	{
		while (*str && (*str == '<' || *str == '>'))
			str++;
		return (str);
	}
	while (*str && !ft_isspace(*str))
	{
		if (*str == '<' || *str == '>')
			break ;
		else if (*str == '\'' || *str == '\"')
		{
			ope = *str++;
			while (*str && *str != ope)
				str++;
			if (*str == ope)
				str++;
		}
		else
			str++;
	}
	return (str);
}

static t_type	get_token_type(char *str)
{
	if (*str && !ft_strncmp(str, ">", 2))
		return (TRUNC);
	else if (*str && !ft_strncmp(str, ">>", 2))
		return (APPEND);
	else if (*str && !ft_strncmp(str, "<", 2))
		return (INPUT);
	else if (*str && !ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	else
		return (WORD);
}

static int	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static t_tokens	*make_new_token(char *str, int len, t_tokens **tokens,
		t_tokens *last)
{
	t_tokens	*new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_token)
		return (NULL);
	new_token->token = ft_strndup(str, len);
	if (!new_token->token)
		return (NULL);
	if (has_quote(new_token->token))
		new_token->type = HAVE_QUOTE;
	else
		new_token->type = get_token_type(new_token->token);
	new_token->next = NULL;
	if (!*tokens)
		*tokens = new_token;
	else
		last->next = new_token;
	return (new_token);
}

t_tokens	*pre_tokenizer(char *str)
{
	t_tokens	*tokens;
	t_tokens	*last_token;
	char		*start;

	tokens = NULL;
	last_token = NULL;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		start = str;
		str = get_token_size(start);
		last_token = make_new_token(start, str - start, &tokens, last_token);
		if (!last_token)
		{
			free_tokens(&tokens);
			return (NULL);
		}
	}
	return (tokens);
}
