/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:52:30 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 17:57:07 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fargs	**execpipe_static_pack(t_fargs **pack)
{
	static t_fargs	**p = NULL;

	if (pack)
		p = pack;
	return (p);
}

void	execpipe_exitfree(int signal)
{
	t_fargs	**pack;

	(void)signal;
	pack = execpipe_static_pack(NULL);
	free_pack(*pack);
	*pack = NULL;
	exit(130);
}

void	execpipe_free_environ(char **environ)
{
	int	i;

	i = -1;
	while (environ[++i])
		free(environ[i]);
	free(environ);
}

void	execpipe_coredump(int signal)
{
	t_fargs	**pack;

	(void)signal;
	pack = execpipe_static_pack(NULL);
	free_pack(*pack);
	*pack = NULL;
	exit(131);
}
