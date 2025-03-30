/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:42:34 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/30 13:09:26 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_vars_and_words(char *str)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

static char	**split_str_to_words(char *str)
{
	char	**words;
	int		count;
	int		i;
	int		j;

	words = (char **)malloc(sizeof(char *) * (count_vars_and_words(str) + 1));
	if (!words)
		return (NULL);
	count = 0;
	i = 0;
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '$')
			while (str[j] && str[j] != '\'' && str[j] != '\"' && str[j] != '$')
				j++;
		else
			while (str[j] && str[j] != '$')
				j++;
		words[count++] = ft_strndup(&str[i], j - i);
		if (!words[count - 1])
			return (free_strs(words), NULL);
		i = j;
	}
	return (words);
}

static char	*concat_words(char **words)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	while (words[i])
	{
		size += ft_strlen(words[i]);
		i++;
	}
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, words[0], size + 1);
	i = 1;
	while (words[i])
	{
		ft_strlcat(new, words[i], size + 1);
		i++;
	}
	return (new);
}

char	*replace_vars_for_wild(char *str, t_var **varlist)
{
	t_var	*var;
	char	**words;
	char	*new;
	int		count;

	words = split_str_to_words(str);
	if (!words)
		return (NULL);
	count = 0;
	while (words[count])
	{
		if (words[count][0] == '$')
		{
			var = get_var(varlist, &words[count][1]);
			free(words[count]);
			words[count] = ft_strdup(var->value);
			if (!words[count])
				return (free_strs(words), NULL);
		}
		count++;
	}
	new = concat_words(words);
	free_strs(words);
	return (new);
}
