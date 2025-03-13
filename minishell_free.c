/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:42:18 by haito             #+#    #+#             */
/*   Updated: 2025/03/13 18:45:53 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_brackets()
{
}

void	free_builtin_cmds(char **builtin_cmds)
{
	int	i;

	i = 0;
	while (builtin_cmds[i])
		free(builtin_cmds[i++]);
	free(builtin_cmds);
}
