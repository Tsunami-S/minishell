/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:23:38 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/23 11:22:42 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_top(t_wild **file, char **words, char *name)
{
	char *trimed_name;
	t_wild *head;
	int i;

	head = *file;
	if(!head->flag || !name)
		return NULL;
	trimed_name = ft_strdup(name);
	if(!trimed_name)
		return NULL;
	i = 0;
	if(!ft_strcmp(words[i], "./"))
		i++;
	if(words[i][0] == '*')
		return trimed_name;
	if(ft_strncmp(trimed_name, words[i], ft_strlen(words[i])))
	{
		head->flag = 0;
		free(trimed_name);
		return NULL;
	}
	ft_strlcpy(trimed_name, &trimed_name[ft_strlen(words[i])], ft_strlen(&trimed_name[ft_strlen(words[i])]) + 1);
	return trimed_name;
}

char *check_bottom(t_wild **file, char **words, char *name)
{
	t_wild *head;
	int i;
	int wlen;
	int nlen;

	head = *file;
	if(!head->flag || !name)
		return NULL;
	i = 0;
	while(words[i] && words[i + 1] && words[i + 1][0] != '/')
		i++;
	if(words[i][0] == '*')
		return name;
	wlen = ft_strlen(words[i]) - 1;
	nlen = ft_strlen(name) - 1;
	while(wlen >= 0)
	{
		if(words[i][wlen] != name[nlen])
		{
			head->flag = 0;
			free(name);
			return NULL;
		}
		wlen--;
		nlen--;
	}
	name[nlen + 1] = '\0';
	return name;
}

void check_dir(t_wild **file, char **words)
{
	int i;
	t_wild *head;

	head = *file;
	if(!head->flag)
		return;
	while(words[i] && words[i + 1])
		i++;
	if(words[i][0] != '/')
		return;
	if(head->type != DT_DIR)
		head->flag = 0;
}
