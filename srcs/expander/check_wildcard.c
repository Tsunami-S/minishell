/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:21:12 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/30 14:28:41 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concat_strs(char **prev_str, char **next_str)
{
	char	*new_str;

	new_str = ft_strjoin(*prev_str, *next_str);
	free(*prev_str);
	free(*next_str);
	if (!new_str)
		return (NULL);
	return (new_str);
}

static t_splited	*make_new_splited_word(t_splited **splited,
		t_splited **next)
{
	t_splited	*new;
	t_splited	*head;
	int			i;

	head = *splited;
	new = (t_splited *)malloc(sizeof(t_splited));
	if (!new)
		return (NULL);
	i = 0;
	while (head->str[i] && head->str[i] != '/')
		i++;
	if (!i && head->str[0] == '/')
	{
		head->type = PLAIN;
		i = 1;
	}
	new->str = strdup(&head->str[i]);
	if (!new->str)
		return (free(new), NULL);
	new->type = PLAIN;
	head->str[i] = '\0';
	new->next = *next;
	return (new);
}

static void	make_new_splited(t_splited **splited)
{
	t_splited	*head;
	t_splited	*tmp;

	head = *splited;
	while (head)
	{
		tmp = NULL;
		if (head->type != WILDS && has_char(head->str, '/'))
			tmp = make_new_splited_word(&head, &(head->next));
		if (tmp)
			head->next = tmp;
		head = head->next;
	}
	head = *splited;
	while (head)
	{
		if (head->type == PLAIN && head->next && head->next->type == PLAIN)
		{
			head->str = concat_strs(&(head->str), &(head->next->str));
			tmp = head->next;
			head->next = head->next->next;
			free(tmp);
		}
		head = head->next;
	}
}

static char	*get_new_token(t_splited **splited)
{
	t_splited	*head;
	int			len;
	char		*new_token;

	head = *splited;
	if (!head->str)
		return (NULL);
	len = 0;
	while (head)
	{
		len += ft_strlen(head->str);
		head = head->next;
	}
	new_token = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_token)
		return (NULL);
	new_token[0] = '\0';
	head = *splited;
	while (head)
	{
		ft_strlcat(new_token, head->str, len + 1);
		head = head->next;
	}
	return (new_token);
}

t_tokens	*check_wildcard(t_splited **splited)
{
	t_tokens	*start;
	t_splited	*head;

	head = *splited;
	while (head && head->type != WILDS)
		head = head->next;
	if (!head || !head->str)
	{
		start = (t_tokens *)malloc(sizeof(t_tokens));
		if (!start)
			return (NULL);
		start->next = NULL;
		start->type = WORD;
		start->token = get_new_token(splited);
	}
	else
	{
		make_new_splited(splited);
		start = expand_wildcard(splited);
	}
	free_splited(splited);
	return (start);
}
