/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:00:14 by haito             #+#    #+#             */
/*   Updated: 2025/03/07 15:57:19 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	wordlen(const char *str, char **sep)
// {
// 	int	count;
// 	int	length;

// 	count = 0;
// 	length = ft_strlen(str);
// 	while (str[count])
// 	{
// 		while (i <= length && sep[++n])
// 		{
// 			if (i <= length - (int)ft_strlen(sep[n])
// 				&& ft_strncmp(str + i, sep[n], (int)ft_strlen(sep[n])) == 0)
// 			{
// 				count++;
// 				i += (int)ft_strlen(sep[n]);
// 				break ;
// 			}
// 		}
// 	}
// 	return (count);
// }

int	count_sep(const char *str, char **sep, int length, int count)
{
	int	i;
	int	n;

	i = 0;
	while (str[i])
	{
		n = -1;
		while (i < length && str[i] == ' ')
			i++;
		while (i <= length && sep[++n])
		{
			if (i <= length - (int)ft_strlen(sep[n])
				&& ft_strncmp(str + i, sep[n], (int)ft_strlen(sep[n])) == 0)
			{
				count++;
				i += (int)ft_strlen(sep[n]);
				break ;
			}
		}
		while (i < length && str[i] != ' ' && str[i] != '|'
			&& (i <= length - (int)ft_strlen(sep[n])
				&& ft_strncmp(str + i, sep[1], (int)ft_strlen(sep[1])) != 0))
			i++;
	}
	return (count);
}

char	*put_word(const char *str, const char **sep, int *length_word)
{
	int		i;
	char	*word;

	i = 0;
	*length_word = wordlen(str, sep);
	// word = (char *)malloc((*length_word + 1) * sizeof(char));
	// if (word == 0)
	// 	return (0);
	// while (i < *length_word)
	// {
	// 	word[i] = str[i];
	// 	i++;
	// }
	// word[i] = '\0';
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
	char	**ret;
	int		n;
	int		i;
	int		count;
	int		count_of_sep;
	int		length_word;

	count_of_sep = count_sep(str, sep, length, 0);
	ret = (char **)malloc((count_of_sep + 2) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	count = 0;
	ret[count++] = put_word(str, sep, &length_word);
	while (str[i] && count < count_of_sep + 1)
	{
		n = -1;
		while (i < length && str[i] == ' ')
			i++;
		while (i <= length && sep[++n])
		{
			if (i <= length - (int)ft_strlen(sep[n])
				&& ft_strncmp(str + i, sep[n], (int)ft_strlen(sep[n])) == 0)
			{
				ret[count++] = put_word(str + i, sep, &length_word);
				i += length_word;
				break ;
			}
		}
		while (i < length && str[i] != ' ' && str[i] != '|'
			&& (i <= length - (int)ft_strlen(sep[n])
				&& ft_strncmp(str + i, sep[1], (int)ft_strlen(sep[1])) != 0))
			i++;
	}
	ret[count] = NULL;
	return (ret);
}
