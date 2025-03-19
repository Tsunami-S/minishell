/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:30:29 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/19 14:45:53 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*make_new_token(char *str, t_tokens *prev, t_tokens *next)
{
	t_tokens	*new;
	int			len;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->token = ft_strdup(str);
	if (!new->token)
	{
		free(new);
		return (NULL);
	}
	len = ft_strlen(new->token);
	len--;
	if (ft_isspace(new->token[len]))
	{
		while (ft_isspace(new->token[len]))
			len--;
		new->token[len + 1] = '\0';
	}
	prev->next = new;
	new->next = next;
	new->type = WORD;
	return (new);
}

static int	trim_space(t_tokens *prev, t_tokens *next, char **token)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = *token;
	while (ft_isspace(str[i]))
		i++;
	ft_strlcpy(str, &str[i], ft_strlen(&str[i]) + 1);
	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '=')
		i++;
	j = 0;
	while (ft_isspace(str[i + j]))
		j++;
	if (str[i + j] && str[i] != '=')
	{
		if (!make_new_token(&str[i + j], prev, next))
			return (ERROR);
		str[i] = '\0';
	}
	return (SUCCESS);
}

int	more_tokenizer(t_tokens **tokens)
{
	t_tokens	*head;

	head = *tokens;
	while (head)
	{
		if (head->type != HAVE_QUOTE)
			if (trim_space(head, head->next, &(head->token)) == ERROR)
				return (ERROR);
		head = head->next;
	}
	return (SUCCESS);
}
