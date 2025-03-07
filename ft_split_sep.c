/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:00:14 by haito             #+#    #+#             */
/*   Updated: 2025/03/07 19:51:51 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(const char *str, int i, char **sep)
{
	int	n;

	n = 0;
	while (sep[n])
	{
		if (ft_strncmp(&str[i], sep[n], ft_strlen(sep[n])) == 0)
			return (ft_strlen(sep[n]));
		n++;
	}
	return (0);
}

int	wordlen(const char *str, char **sep)
{
	int	length;
	int	i;
	int	sep_len;

	i = 0;
	sep_len = 0;
	length = ft_strlen(str);
	while (i < length && str[i] == ' ')
		i++;
	while (i < length)
	{
		sep_len = is_sep(str, i, sep);
		if (sep_len > 0)
		{
			i += sep_len;
			break ;
		}
		i++;
	}
	return (i);
}

int	count_sep(const char *str, char **sep, int length, int count)
{
	int	i;
	int	sep_len;

	i = 0;
	while (i < length)
	{
		while (i < length && str[i] == ' ')
			i++;
		sep_len = is_sep(str, i, sep);
		if (sep_len > 0)
		{
			count++;
			i += sep_len;
		}
		else
			i++;
	}
	return (count);
}

char	*put_word(const char *str, char **sep, int *length_word)
{
	char	*word;

	*length_word = wordlen(str, sep);
	printf("%d\n", *length_word);

	word = (char *)malloc((*length_word + 1) * sizeof(char));
	if (word == 0)
		return (NULL);
	ft_strncpy(word, str, *length_word);
	word[*length_word] = '\0';
	return (word);
}

// char	**free_split(char **ret, int n)
// {
// 	while (n--)
// 		free(ret[n]);
// 	free(ret);
// 	return (0);
// }

char	**ft_split_sep(const char *str, char **sep, int length)
{
	printf("pipes: %d\n", count_sep(str, sep, length, 0));
	int		i;
	int		count;
	int		count_of_sep;
	int		length_word;
	char	**ret;

	count_of_sep = count_sep(str, sep, length, 0);
	ret = (char **)malloc((count_of_sep + 2) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i] && count < count_of_sep + 1)
	{
		while (i < length && str[i] == ' ')
			i++;
		ret[count++] = put_word(str + i, sep, &length_word);
		i += length_word;
		while (i < length && str[i] != ' ')
			i++;
	}
	ret[count] = NULL;
	return (ret);
}
