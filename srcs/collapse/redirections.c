/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:00:02 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/22 20:00:02 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	closewait(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (-2);
	if (((status) & 0177) == 0)
	{
		if ((int)(((unsigned)(status) >> 8) & 0xff) != 0)
			return ((int)(((unsigned)(status) >> 8) & 0xff) != 0);
	}
	return (-3);
}

int	run_redir(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	int	pid;

	if (ast_node->token == T_LEFTRDIR)
		pid = run_ldir(ast_node, str, env, root_);
	if (ast_node->token == T_RIGHTRDIR)
		pid = run_rdir(ast_node, str, env, root_);
	if (ast_node->token == T_RAPPEND)
		pid = run_rrdir(ast_node, str, env, root_);
	if (ast_node->token == T_LEFTHRDC)
		pid = run_heredoc(ast_node, str, env, root_);
	closewait(pid);
	return (0);
}
