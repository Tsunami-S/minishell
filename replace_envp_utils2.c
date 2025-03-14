/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envp_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:42:08 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/14 16:59:47 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_var(char *str, char **words, int *i, t_var **varlist)
{
	char	*end;
	char *name;
	t_var *var;

	end = str;
	end++;
	while (*end && *end != '$' && *end != '\'' && *end != '\"'
		&& !ft_isspace(*end))
		end++;
	name = ft_strndup(str + 1, end - str - 1);
	if (!name)
		return (NULL);
	var = get_var(varlist, name);
	if(!var)
		words[*i] = ft_strdup("");
	else
		words[*i] = ft_strdup(var->value);
	if (!words[*i])
		return (NULL);
	*i += 1;
	return (end);
}

static char	*dup_doublequot_text(char *str, char **words, int *i, t_var **varlist)
{
	char	*end;
	char	*start;

	str++;
	end = str;
	start = str;
	while (*end && *end != '\"')
	{
		if (*start == '$')
			end = dup_var(start, words, i, varlist);
		else
		{
			while (*end && *end != '\"' && *end != '$')
				end++;
			words[*i] = ft_strndup(start, end - start);
			if (!words[*i])
				return (NULL);
			*i += 1;
		}
		start = end;
	}
	if (*end == '\"')
		end++;
	return (end);
}

static char	*dup_plain_text(char *str, char **words, int *i)
{
	char	*end;

	end = count_plaintext_size(str);
	words[*i] = ft_strndup(str, end - str);
	if (!words[*i])
		return (NULL);
	*i += 1;
	return (end);
}

static char	*dup_singlequot_text(char *str, char **words, int *i)
{
	char	*end;

	str++;
	end = str;
	while (*end && *end != '\'')
		end++;
	words[*i] = ft_strndup(str, end - str);
	if (!words[*i])
		return (NULL);
	*i += 1;
	if (*end == '\'')
		end++;
	return (end);
}

char	**split_token(char *token, int malloc_size, t_var **varlist)
{
	char	**words;
	int		i;

	words = (char **)malloc(sizeof(char *) * (malloc_size + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (*token)
	{
		if (*token == '\"')
			token = dup_doublequot_text(token, words, &i, varlist);
		else if (*token == '\'')
			token = dup_singlequot_text(token, words, &i);
		else if (*token == '$')
			token = dup_var(token, words, &i, varlist);
		else
			token = dup_plain_text(token, words, &i);
		if(!token)
		{
			free_words(words, malloc_size);
			return NULL;
		}
	}
	words[i] = NULL;
	return (words);
}
