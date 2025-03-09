/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:39:18 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/10 00:14:26 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************/
// [*] tokenizer (split cmds to valiable token)
// [ ] replace envvar
// [ ] redirect fds
// [ ] builtin check
// [ ] change list to array for cmd
// [*] make_fullpath
// [*] execve
// [ ] free
/***********************************/

static void free_child(char **cmds, char *fullpath)
{
	int i;

	if(cmds)
	{
		i = 0;
		while(cmds[i])
			free(cmds[i++]);
		free(cmds);
	}
	free(fullpath);
}

void	continue_child(char *str, char **envp)
{
	t_tokens *tokens;
	char **cmds;
	char *fullpath;

	cmds = NULL;
	fullpath = NULL;

	//cmds = ft_split(str, ' ');
	
	tokens = tokenizer(str);
	//replace_envvar(&tokens);
	//redirect_fds(&tokens);
	//check builtin
	//make_cmds(&tokens);
	make_fullpath(cmds[0], envp, &fullpath);
	execve(fullpath, cmds, envp);
	free_child(cmds, fullpath);
	error_process();
}
