/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:06:31 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 17:57:18 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmdpath(char **av, t_map **env)
{
	char	*result;
	char	*tmp;
	char	**path;
	int		i;
	int		code;

	tmp = ft_strdup(av[0]);
	path = exportpath(*env);
	if (!path)
		path = (char **){0};
	result = NULL;
	code = ft_find_cmd_path(tmp, path, &result);
	free(tmp);
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	if (!result)
		return (code);
	if (code)
		return (free(result), code);
	free(av[0]);
	av[0] = result;
	return (free(av[0]), av[0] = result, 0);
}

int	f_exec_inpipe(t_fargs *info)
{
	char	**environ;
	int		i;

	execpipe_static_pack(&info);
	signal(SIGINT, execpipe_exitfree);
	signal(SIGQUIT, execpipe_coredump);
	environ = export(*(info->env));
	i = cmdpath(info->av, info->env);
	if (i)
	{
		free_pack(info);
		execpipe_free_environ(environ);
		exit(i);
	}
	execve(info->av[0], info->av, environ);
	ft_error("execve: ", strerror(errno), NULL, 1);
	free_pack(info);
	execpipe_free_environ(environ);
	return (1);
}
