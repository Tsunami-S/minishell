/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:39:02 by haito             #+#    #+#             */
/*   Updated: 2025/03/07 14:22:12 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_sep(void)
{
	char	**seps;

	seps = malloc(sizeof(char *) * 4);
	if (!seps)
		error_process();
	seps[0] = ft_strdup("||");
	if (!seps[0])
		error_process();
	seps[1] = ft_strdup("&&");
	if (!seps[1])
		error_process();
	seps[2] = ft_strdup("|");
	if (!seps[2])
		error_process();
	seps[3] = NULL;
	return (seps);
}
