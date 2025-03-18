/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:08:58 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/18 22:14:44 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(char *token)
{
	int		i;
	int		flag;
	char	*var;

	flag = 0;
	if (ft_isdigit(token[0]))
		flag = 1;
	i = 0;
	while (token[i] && token[i] != '=')
	{
		if (!ft_strncmp(&token[i], "+=", 2))
			break ;
		if (!ft_isalnum(token[i]) && token[i] != '_')
			flag = 1;
		i++;
	}
	if (!flag)
		return (SUCCESS);
	var = ft_strndup(token, i);
	if (!var)
		return (builtin_error(errno, "malloc error"));
	return (builtin_error(EXPORTERROR, var));
}

char	*get_new_value(char *str)
{
	char	*value;
	char	**words;
	int		value_size;
	int		i;

	words = ft_split(str, ' ');
	if (!words)
		return (NULL);
	value_size = 0;
	i = 0;
	while (words[i])
		value_size += ft_strlen(words[i++]) + 1;
	value = (char *)malloc(sizeof(char) * (value_size + 1));
	if (!value)
		return (free_strs(words), NULL);
	ft_strlcpy(value, words[0], value_size);
	i = 1;
	while (words[i])
	{
		ft_strlcat(value, " ", value_size);
		ft_strlcat(value, words[i++], value_size);
	}
	free_strs(words);
	return (value);
}

static int	append_var(t_var **varlist, char *str, int name_len)
{
	char	*name;
	char	*value;
	char	*base_value;
	t_var	*base;

	name = ft_strndup(str, name_len);
	if (!name)
		return (builtin_error(errno, "malloc error"));
	value = get_new_value(&str[name_len + 2]);
	if (!value)
		return (free(name), builtin_error(errno, "malloc error"));
	base = get_var(varlist, name);
	if (!base)
		add_var(varlist, name, value);
	else
	{
		free(name);
		base_value = base->value;
		base->value = ft_strjoin(base_value, value);
		free(base_value);
		free(value);
		if (!base->value)
			return (builtin_error(errno, "malloc error"));
	}
	return (SUCCESS);
}

static int	add_newvar(t_var **varlist, char *str, int name_len)
{
	char	*name;
	char	*value;

	name = ft_strndup(str, name_len);
	if (!name)
		return (builtin_error(errno, "malloc error"));
	if (!str[name_len])
		value = NULL;
	else
	{
		value = get_new_value(&str[name_len + 1]);
		if (!value)
		{
			free(name);
			return (builtin_error(errno, "malloc error"));
		}
	}
	add_var(varlist, name, value);
	return (SUCCESS);
}

int	builtin_export(t_tokens **tokens, t_var **varlist)
{
	t_tokens	*head;
	int			i;

	head = (*tokens)->next;
	if (!head)
		return (builtin_export_list(varlist));
	while (head)
	{
		if (check_syntax(head->token) == SUCCESS)
		{
			i = 0;
			while (head->token[i] && head->token[i] != '='
				&& head->token[i] != '+')
				i++;
			if (head->token[i] == '+')
				append_var(varlist, head->token, i);
			else
				add_newvar(varlist, head->token, i);
		}
		head = head->next;
	}
	return (EXIT_SUCCESS);
}
