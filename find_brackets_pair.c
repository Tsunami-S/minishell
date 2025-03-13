/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_brackets_pair.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:50:47 by haito             #+#    #+#             */
/*   Updated: 2025/03/13 11:04:09 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_brackets_pair(int i, t_brackets *brackets)
{
	int	n;

	n = 0;
	while (brackets->pair[n][0] != i)
		n++;
	return (brackets->pair[n][1]);
}

void	save_pair(t_brackets *b, int i)
{
	b->pair[b->countof_pair][0] = b->data[b->top--];
	b->pair[b->countof_pair++][1] = i;
	if (b->countof_pair < MAX_STACK_BRACKETS)
	{
		b->pair[b->countof_pair][0] = -1;
		b->pair[b->countof_pair][1] = -1;
	}
}

int	skip_quotes(const char *input, int i, char quote)
{
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
		return (error_process(), printf("no pair %c\n", quote), -1);
	return (i);
}

void	process_bracket(const char *input, t_brackets *b, int i)
{
	if (input[i] == '(')
	{
		if (b->top < MAX_STACK_BRACKETS - 1)
			b->data[++b->top] = i;
		else
			error_process();
	}
	else if (input[i] == ')')
	{
		if (b->top != -1)
			save_pair(b, i);
		else
			error_process();
	}
}

int	find_brackets_pair(const char *input, t_brackets *b)
{
	int	length;
	int	i;

	b->top = -1;
	b->countof_pair = 0;
	b->pair[b->countof_pair][0] = -1;
	b->pair[b->countof_pair][1] = -1;
	length = ft_strlen(input);
	i = 0;
	while (i < length)
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quotes(input, i, input[i]);
		else
			process_bracket(input, b, i);
		if (i == -1)
			return (-1);
		i++;
	}
	if (b->top >= 0)
		return (error_process(), printf("error\n"), -1);
	return (0);
}
