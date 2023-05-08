/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 23:13:21 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 18:50:26 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
