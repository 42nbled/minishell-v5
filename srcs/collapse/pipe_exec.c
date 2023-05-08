/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:06:31 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 01:23:24 by cde-sede         ###   ########.fr       */
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
	result = NULL;
	code = ft_find_cmd_path(tmp, path, &result);
	free(tmp);
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	if (!result)
		return (1);
	if (code)
	{
		free(result);
		return (code);
	}
	free(av[0]);
	av[0] = result;
	return (0);
}

static t_fargs	**pack__(t_fargs **pack)
{
	static t_fargs	**p = NULL;

	if (pack)
		p = pack;
	return (p);
}

static void	exitfree(int signal)
{
	t_fargs	**pack;

	(void)signal;
	pack = pack__(NULL);
	free_pack(*pack);
	*pack = NULL;
	exit(130);
}

static void	free_environ(char **environ)
{
	int	i;

	i = -1;
	while (environ[++i])
		free(environ[i]);
	free(environ);
}

int	f_exec_inpipe(t_fargs *info)
{
	char	**environ;
	int		i;

	pack__(&info);
	signal(SIGINT, exitfree);
	signal(SIGQUIT, SIG_IGN);
	environ = export(*(info->env));
	i = cmdpath(info->av, info->env);
	if (i)
	{
		free_pack(info);
		free_environ(environ);
		exit(i);
	}
	execve(info->av[0], info->av, environ);
	ft_error("execve: ", strerror(errno), NULL, 1);
	free_pack(info);
	free_environ(environ);
	return (1);
}
