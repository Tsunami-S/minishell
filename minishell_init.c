/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:39:02 by haito             #+#    #+#             */
/*   Updated: 2025/03/13 19:03:10 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**init_sep(void)
// {
// 	char	**cmds;

// 	cmds = malloc(sizeof(char *) * 4);
// 	if (!cmds)
// 		error_process();
// 	cmds[0] = ft_strdup("||");
// 	if (!cmds[0])
// 		error_process();
// 	cmds[1] = ft_strdup("&&");
// 	if (!cmds[1])
// 		error_process();
// 	cmds[2] = ft_strdup("|");
// 	if (!cmds[2])
// 		error_process();
// 	cmds[3] = NULL;
// 	return (cmds);
// }

void	init_builtin_cmds2(char	**cmds)
{
	cmds[4] = ft_strdup("unset");
	if (!cmds[4])
		error_process();
	cmds[5] = ft_strdup("env");
	if (!cmds[5])
		error_process();
	cmds[6] = ft_strdup("exit");
	if (!cmds[6])
		error_process();
}

char	**init_builtin_cmds(void)
{
	char	**cmds;
	int		i;

	cmds = malloc(sizeof(char *) * 8);
	if (!cmds)
		error_process();
	i = 0;
	while (i < 8)
		cmds[i++] = NULL;
	cmds[0] = ft_strdup("echo");
	if (!cmds[0])
		error_process();
	cmds[1] = ft_strdup("cd");
	if (!cmds[1])
		error_process();
	cmds[2] = ft_strdup("pwd");
	if (!cmds[2])
		error_process();
	cmds[3] = ft_strdup("export");
	if (!cmds[3])
		error_process();
	init_builtin_cmds2(cmds);
	return (cmds);
}
