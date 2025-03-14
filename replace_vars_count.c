/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envp_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:53:16 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/14 17:50:44 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*count_plaintext_size(char *str)
{
	while (*str && *str != '$' && *str != '\'' && *str != '\"')
		str++;
	return (str);
}

static char	*count_singlequot_text_size(char *str)
{
	str++;
	if (*str == '\'')
		str++;
	while (*str && *str != '\'')
		str++;
	if (*str == '\'')
		str++;
	return (str);
}

static char	*count_envvar_size(char *str)
{
	if (*str == '$')
		str++;
	while (*str && *str != '$' && *str != '\'' && *str != '\"'
		&& !ft_isspace(*str))
		str++;
	return (str);
}

static char	*count_doublequot_text_size(char *str, int *malloc_size)
{
	*malloc_size -= 1;
	if (*str == '\"')
		str++;
	while (*str && *str != '\"')
	{
		*malloc_size += 1;
		if (*str == '$')
			str = count_envvar_size(str);
		else
		{
			while (*str && *str != '\"' && *str != '$')
				str++;
		}
	}
	if (*str == '\"')
		str++;
	return (str);
}

int	count_words_and_vars(char *str)
{
	int	malloc_size;

	malloc_size = 0;
	while (*str)
	{
		malloc_size++;
		if (*str && *str != '$' && *str != '\'' && *str != '\"')
			str = count_plaintext_size(str);
		else if (*str == '\'')
			str = count_singlequot_text_size(str);
		else if (*str == '$')
			str = count_envvar_size(str);
		else if (*str == '\"')
			str = count_doublequot_text_size(str, &malloc_size);
	}
	return (malloc_size);
}
