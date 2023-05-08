/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 23:13:21 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 18:23:39 by cde-sede         ###   ########.fr       */
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
	{
		path = malloc(sizeof(char *));
		path[0] = NULL;
	}
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

static void	coredump(int signal)
{
	t_fargs	**pack;

	(void)signal;
	pack = pack__(NULL);
	free_pack(*pack);
	*pack = NULL;
	exit(131);
}

void	exec_free_environ(char **environ)
{
	int	i;

	i = -1;
	while (environ[++i])
		free(environ[i]);
	free(environ);
}

static	int	wait_exec(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (ft_error("core dump", "", "", 131));
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
		return (ft_error("segmentation fault", "", "", 139));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (status);
	return (1);
}

int	f_exec(t_fargs *info)
{
	char	**environ;
	int		pid;
	int		i;

	pack__(&info);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, exitfree);
		signal(SIGQUIT, coredump);
		environ = export(*(info->env));
		i = cmdpath(info->av, info->env);
		if (i)
		{
			free_pack(info);
			exec_free_environ(environ);
			exit(i);
		}
		execve(info->av[0], info->av, environ);
		ft_error("execve: ", strerror(errno), "", 1);
		free_pack(info);
		exec_free_environ(environ);
		exit(1);
	}
	return (wait_exec(pid));
}
