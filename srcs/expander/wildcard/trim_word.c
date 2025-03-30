/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:23:38 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/30 13:09:37 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_word_start(t_wild **file, t_splited **splited, char *name)
{
	char		*trimed_name;
	t_wild		*target;
	t_splited	*head;

	target = *file;
	if (!target->flag || !name)
		return (NULL);
	trimed_name = ft_strdup(name);
	if (!trimed_name)
		return (NULL);
	head = *splited;
	if (head && head->type == WILDS)
		return (trimed_name);
	if (ft_strncmp(trimed_name, head->str, ft_strlen(head->str)))
	{
		target->flag = 0;
		return (free(trimed_name), NULL);
	}
	ft_strlcpy(trimed_name, &trimed_name[ft_strlen(head->str)],
		ft_strlen(&trimed_name[ft_strlen(head->str)]) + 1);
	return (trimed_name);
}

static int	set_len(char *word, char *name, int *wlen, int *nlen)
{
	*wlen = ft_strlen(word) - 1;
	*nlen = ft_strlen(name) - 1;
	if (*nlen < 0)
		return (ERROR);
	return (SUCCESS);
}

char	*trim_word_end(t_wild **file, t_splited **splited, char *name)
{
	t_wild		*target;
	t_splited	*head;
	int			wlen;
	int			nlen;

	target = *file;
	if (!target->flag || !name || !*name)
		return (NULL);
	head = *splited;
	while (head && head->next && head->next->str[0] != '/')
		head = head->next;
	if (head->type == WILDS)
		return (name);
	if (set_len(head->str, name, &wlen, &nlen) == ERROR)
		target->flag = 0;
	while (wlen >= 0 && nlen >= 0)
	{
		if (head->str[wlen--] != name[nlen--])
		{
			target->flag = 0;
			return (NULL);
		}
	}
	name[nlen + 1] = '\0';
	return (name);
}
