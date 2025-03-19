/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars_split2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:42:08 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/19 16:32:11 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		ft_strlcpy(str, &str[i], ft_strlen(&str[i]) + 1);
	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_isspace(str[i]))
			i++;
		if (str[i])
			i++;
		j = 0;
		while (str[i + j] && ft_isspace(str[i + j]))
			j++;
		if (j && str[i + j])
			ft_strlcpy(&str[i], &str[i + j], ft_strlen(&str[i + j]) + 1);
		else
			str[i] = '\0';
	}
	return (str);
}
