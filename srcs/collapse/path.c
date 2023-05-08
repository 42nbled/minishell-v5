/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:12:00 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 05:50:33 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	joinpath(char *prefix, char *cmd, char **result)
{
	char	*dest;

	if (!prefix || !cmd)
		return (1);
	dest = ft_jointhree(prefix, "/", cmd);
	if (!dest)
		return (1);
	*result = dest;
	return (1);
}

static int	ft_try_path(char *cmd, char **path, char **result)
{
	if (!path || !*path)
		return (0);
	joinpath(*path, cmd, result);
	if (!*result)
		return (0);
	if (!access(*result, F_OK | X_OK))
		return (1);
	free(*result);
	*result = NULL;
	return (ft_try_path(cmd, path + 1, result));
}

static int	ft_check_absolute_relative_path(char *cmd)
{
	int	status;

	status = 0;
	if (access(cmd, F_OK))
		return (ft_error(cmd, ": command not found", "", 127));
	if (!access(cmd, F_OK | X_OK))
		return (0);
	ft_error(cmd, ": ", strerror(errno), 1);
	return (126);
}

int	ft_find_cmd_path(char *cmd, char **path, char **result)
{
	if (!cmd)
		return (0);
	if (!*cmd)
		return (ft_error(cmd, ": command not found", "", 127));
	*result = ft_strdup(cmd);
	if (ft_strchr(cmd, '.') || ft_strchr(cmd, '/') || !path || !*path)
		return (ft_check_absolute_relative_path(cmd));
	else
	{
		free(*result);
		*result = NULL;
		if (!*cmd || !ft_try_path(cmd, path, result))
			return (ft_error(cmd, ": command not found", "", 127));
	}
	return (0);
}

char	**exportpath(t_map *env)
{
	char	*tmp;
	char	**path;

	tmp = get_env("PATH", env);
	if (!tmp)
		return (NULL);
	path = ft_split(tmp, ':');
	if (!path)
		return (NULL);
	return (path);
}
