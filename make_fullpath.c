/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fullpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:10:30 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/09 22:28:48 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_original_path(char *cmd)
{
	char	*fullpath;

	fullpath = ft_strdup(cmd);
	if (!fullpath)
		error_process();
	if (access(fullpath, F_OK))
		error_process();
	// exit(strerror(enoent)) no such file or directory
	if (access(fullpath, X_OK))
		error_process();
	// exit_pipex(strerror(eacces)) permission denied
	return (fullpath);
}

static char	*concat_home_with_cmd(char *cmd, char **envp)
{
	char	*fullpath;
	char	*home;

	home = getenv("HOME");
	if (home)
		fullpath = ft_strjoin(home, &cmd[1]);
	else
		fullpath = ft_strdup(cmd);
	if (!fullpath)
		error_process();
	if (access(fullpath, F_OK))
		error_process();
	// exit(strerror(enoent)) no such file or directory
	if (access(fullpath, X_OK))
		error_process();
	// exit_pipex(strerror(eacces)) permission denied
	return (fullpath);
}

static char	**get_paths(char **envp)
{
	char	**paths;
	char	*env_path;

	if (!envp || !*envp)
		return (NULL);
	env_path = getenv("PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(&env_path[5], ':');
	if (!paths)
		error_process();
	return (paths);
}

static char	*concat_path_with_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*fullpath;
	int		i;

	paths = get_paths(envp);
	i = 0;
	while (paths[i])
	{
		fullpath = ft_strjoin_three(paths[i], "/", cmd);
		if (!fullpath)
			error_process();
		if (!access(fullpath, X_OK))
			break ;
		free(fullpath);
		fullpath = NULL;
		i++;
	}
	if (!fullpath)
		error_process();
	// exit_pipex("command not found")
	return (fullpath);
}

void	make_fullpath(char *cmd, char **envp, char **fullpath)
{
	*fullpath = NULL;
	if (!cmd || !cmd[0])
		return ;
	if (cmd[0] == '/' || !ft_strncmp(cmd, "./", 2))
		*fullpath = check_original_path(cmd);
	else if (envp && !ft_strncmp(cmd, "~/", 2))
		*fullpath = concat_home_with_cmd(cmd, envp);
	else if (envp)
		*fullpath = concat_path_with_cmd(cmd, envp);
	else
		*fullpath = check_original_path(cmd);
}
