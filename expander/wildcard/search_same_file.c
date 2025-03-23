/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_same_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:31:24 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/23 11:36:58 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isvalid_secret(t_wild **file, char *word, char *name)
{
	t_wild	*head;

	head = *file;
	if (word[0] != '.' && name[0] == '.')
		head->flag = 0;
	return (head->flag);
}

//static int	isvalid_wildcard(t_wild **files, char *word, char *name)
//{
//	t_wild	*head;
//	int		i;
//
//	head = *files;
//	i = 0;
//	while (name[i])
//	{
//		while (name[i] && name[i] != *word)
//			i++;
//		if (!ft_strncmp(&name[i], word, ft_strlen(word)))
//			return (i + ft_strlen(word));
//		if (name[i])
//			i++;
//		if (!name[i])
//			head->flag = 0;
//	}
//	return (0);
//}
//
//static int	isvalid_file(t_wild **files, char *word, char *name)
//{
//	t_wild	*head;
//
//	head = *files;
//	if (ft_strncmp(name, word, ft_strlen(word)))
//	{
//		head->flag = 0;
//		return (0);
//	}
//	return (ft_strlen(word));
//}

static int set_end(char **words)
{
	int i;
	int end;

	i = 0;
	while(words[i])
		i++;
	end = i;
	if(end > 0 && words[end - 1][0] == '/')
		end -= 1;
	if(end > 0 && words[end - 1][0] != '*')
		end -= 1;
	if(end > 0 && words[end - 1][0] == '*')
		end -= 1;
	return end;
}

static void	manage_flag(t_wild **files, char **words, char *name, int i)
{
	t_wild *head;
	int end;
	char *saved;

	head = *files;
	if(!head->flag || !name)
		return ;
	end = set_end(words);
	while(i < end && head->flag)
	{
		while(*name && ft_strncmp(name, words[i], ft_strlen(words[i])))
			name++;
		if(!*name)
			head->flag = 0;
		else
		{
			saved = name;
			name += ft_strlen(words[i]);
			manage_flag(files, words, name, i + 1);
			if(head->flag)
				break;
			else
				head->flag = 1;
			name = saved + 1;
		}
	}
}

void	search_same_file(t_wild **files, char *str)
{
	t_wild	*head;
	char	**words;
	char	*trimed_name;
	int len;

	if (!*files)
		return ;
	len = count_wild_words(str);
	words = split_wildcards(str, len);
	if (!words)
		return ;
	head = *files;
	while (head)
	{
		if (isvalid_secret(&head, words[0], head->name))
		{
			trimed_name =  check_top(&head, words, head->name);
			trimed_name =  check_bottom(&head, words, trimed_name);
			int index = 0;
			if(!ft_strcmp(words[0], "./"))
				index += 1;
			if(words[index][0] != '*')
				index += 1;
			if(words[index][0] == '*')
				index += 1;
			manage_flag(&head, words, trimed_name, index);
	//		check_dir(&head, words);
			free(trimed_name);
		}
		head = head->next;
	}
	free_strs(words);
}
