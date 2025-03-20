/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:52:57 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/20 20:08:16 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_syntaxerr_msg(char *msg)
{
	int		total_len;
	char	*strerr;

	total_len = ft_strlen("minishell: ");
	total_len += ft_strlen("syntax error near unexpected token '");
	total_len += ft_strlen(msg) + 3;
	strerr = (char *)malloc(sizeof(char) * total_len);
	if (!strerr)
		return ;
	ft_strlcpy(strerr, "minishell: ", total_len);
	ft_strlcat(strerr, "syntax error near unexpected token '", total_len);
	ft_strlcat(strerr, msg, total_len);
	ft_strlcat(strerr, "'\n", total_len);
	ft_eprintf("%s", strerr);
	free(strerr);
}

static void	put_errmsg(char *msg1, char *msg2)
{
	int		total_len;
	char	*strerr;

	if (!msg1)
		return ;
	total_len = ft_strlen("minishell: ");
	total_len += ft_strlen(msg1) + ft_strlen(msg2) + 4;
	strerr = (char *)malloc(sizeof(char) * total_len);
	if (!strerr)
		return ;
	ft_strlcpy(strerr, "minishell: ", total_len);
	ft_strlcat(strerr, msg1, total_len);
	ft_strlcat(strerr, ": ", total_len);
	ft_strlcat(strerr, msg2, total_len);
	ft_strlcat(strerr, "\n", total_len);
	ft_eprintf("%s", strerr);
	free(strerr);
}

void	exit_child(t_child *child, int status, int errnum, char *msg)
{
	if (errnum == CMDERROR)
		put_errmsg(msg, "command not found");
	else if (errnum == REDIRECTERROR)
		put_syntaxerr_msg(msg);
	else if (errnum == AMBIGUOUS)
		put_errmsg(msg, "ambiguous redirect");
	else if (errnum > 0)
		put_errmsg(msg, strerror(errnum));
	if (child->tokens)
		free_tokens(child->tokens);
	if (child->varlist)
		free_varlist(child->varlist);
	if (child->cmds)
		free(child->cmds);
	if (child->fullpath)
		free(child->fullpath);
	if (child->envp)
		free_strs(child->envp);
	if (child->paths)
		free_strs(child->paths);
	if (child->tmpfile)
	{
		unlink(child->tmpfile);
		free(child->tmpfile);
	}
	exit(status);
}
