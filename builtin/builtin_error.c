/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:09:01 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/16 16:58:00 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_cmderr_msg(char *msg)
{
	int		total_len;
	char	*strerr;

	total_len = ft_strlen("minishell: ");
	total_len += ft_strlen("command not found");
	total_len += ft_strlen(msg) + 4;
	strerr = (char *)malloc(sizeof(char) * total_len);
	if (!strerr)
		return ;
	ft_strlcpy(strerr, "minishell: ", total_len);
	ft_strlcat(strerr, msg, total_len);
	ft_strlcat(strerr, ": command not found\n", total_len);
	ft_eprintf("%s", strerr);
	free(strerr);
}

static void	put_exporterr_msg(char *msg)
{
	int		total_len;
	char	*strerr;

	total_len = ft_strlen("minishell: export`");
	total_len = ft_strlen("': not a valid identifier\n");
	total_len += ft_strlen(msg) + 2;
	strerr = (char *)malloc(sizeof(char) * total_len);
	if (!strerr)
		return ;
	ft_strlcpy(strerr, "minishell: export`", total_len);
	ft_strlcat(strerr, msg, total_len);
	ft_strlcat(strerr, "': not a valid identifier\n", total_len);
	ft_eprintf("%s", strerr);
	free(strerr);
}

static void	put_redirecterr_msg(char *msg)
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

static void	put_errmsg(char *msg, int errnum)
{
	int		total_len;
	char	*strerr;

	total_len = ft_strlen("minishell: ");
	total_len += ft_strlen(strerror(errnum)) + ft_strlen(msg) + 4;
	strerr = (char *)malloc(sizeof(char) * total_len);
	if (!strerr)
		return ;
	ft_strlcpy(strerr, "minishell: ", total_len);
	ft_strlcat(strerr, msg, total_len);
	ft_strlcat(strerr, ": ", total_len);
	ft_strlcat(strerr, strerror(errnum), total_len);
	ft_strlcat(strerr, "\n", total_len);
	ft_eprintf("%s", strerr);
	free(strerr);
}

int builtin_error(int errnum, char *msg)
{
	if (errnum == CMDERROR)
		put_cmderr_msg(msg);
	else if (errnum == REDIRECTERROR)
		put_redirecterr_msg(msg);
	else if (errnum == EXPORTERROR)
		put_exporterr_msg(msg);
	else
		put_errmsg(msg, errnum);
	return (EXIT_FAILURE);
}
