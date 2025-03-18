/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:42:08 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/19 00:38:18 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_var(char *str, char **words, int *i, t_var **varlist)
{
	char	*end;
	char	*name;
	t_var	*var;

	end = str;
	end++;
	if (*end == '?')
		end++;
	else
		while (*end && (ft_isalnum(*end) || *end == '_'))
			end++;
	name = ft_strndup(str + 1, end - str - 1);
	if (!name)
		return (NULL);
	var = get_var(varlist, name);
	free(name);
	if (!var || !var->value)
		words[*i] = ft_strdup("");
	else
		words[*i] = ft_strdup(var->value);
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

static char	*dup_doublequot_text(char *str, char **words, int *i,
		t_var **varlist)
{
	char	*end;
	char	*start;

	end = str + 1;
	start = str + 1;
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
	return (end + 1);
}

static char	*dup_plain_text(char *str, char **words, int *i)
{
	char	*end;

	end = str;
	while (*end == '$')
		end++;
	while (*end && *end != '$' && *end != '\'' && *end != '\"')
		end++;
	words[*i] = ft_strndup(str, end - str);
	if (!words[*i])
		return (NULL);
	*i += 1;
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
		if (*token == '$' && (ft_isalnum(*(token + 1)) || *(token + 1) == '_'))
			token = dup_var(token, words, &i, varlist);
		else if (!ft_strncmp(token, "$?", 2))
			token = dup_var(token, words, &i, varlist);
		else if (*token == '\'')
			token = dup_singlequot_text(token, words, &i);
		else if (*token == '\"')
			token = dup_doublequot_text(token, words, &i, varlist);
		else
			token = dup_plain_text(token, words, &i);
		if (!token)
			return (free_words(words, malloc_size), NULL);
	}
	words[i] = NULL;
	return (words);
}
