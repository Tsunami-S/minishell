/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:32:04 by haito             #+#    #+#             */
/*   Updated: 2025/03/16 17:47:53 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*error_add_char(int *i, char *cmds)
{
	if (cmds)
		free(cmds);
	if (i)
		*i = ERROR;
	return (NULL);
}

int	error_handle_brackets(int error_num)
{
	if (error_num == ERRNO_ONE)
		ft_eprintf("minishell: syntax error near unexpected token `('\n");
	if (error_num == ERRNO_TWO)
		ft_eprintf("minishell: syntax error near unexpected token `)'\n");
	if (error_num == ERRNO_THREE)
		perror("minishell: malloc error: ");
	if (error_num == ERRNO_FOUR)
		ft_eprintf("minishell: syntax error after `)'\n");
	return (ERROR);
}

int	error_node(int error_num)
{
	if (error_num == ERRNO_ONE)
		ft_eprintf("minishell: malloc error: Cannot allocate memory\n");
	return (ERROR);
}

int	error_pipe(int error_num)
{
	if (error_num == ERRNO_ONE)
		ft_eprintf("minishell: syntax error has operator at the head\n");
	if (error_num == ERRNO_TWO)
		ft_eprintf("minishell: syntax error has operator at the end\n");
	if (error_num == ERRNO_THREE)
		ft_eprintf("minishell: pipe error\n");
	if (error_num == ERRNO_FOUR)
		ft_eprintf("minishell: syntax error has operator in a row\n");
	return (ERROR);
}
