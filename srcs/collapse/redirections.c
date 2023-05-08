/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:00:02 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 18:23:40 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	closewait(int pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (131);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
		return (ft_error("segmentation fault", "", "", 139));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (status);
	return (0);
}

int	run_redir(t_btree *ast_node, t_map **env, t_btree *root_, t_token *last)
{
	int		pid;
	t_token	tmp;

	tmp = *last;
	*last = ast_node->token;
	if ((ast_node->token == T_LEFTRDIR || ast_node->token == T_LEFTHRDC)
		&& (tmp == T_LEFTRDIR || tmp == T_LEFTHRDC))
		return (run_redir_inredir(ast_node, env, root_));
	if ((ast_node->token == T_RIGHTRDIR || ast_node->token == T_RAPPEND)
		&& (tmp == T_RIGHTRDIR || tmp == T_RAPPEND))
		return (run_redir_inredir(ast_node, env, root_));
	if (ast_node->token == T_LEFTRDIR)
		pid = run_ldir(ast_node, env, root_);
	else if (ast_node->token == T_RIGHTRDIR)
		pid = run_rdir(ast_node, env, root_);
	else if (ast_node->token == T_RAPPEND)
		pid = run_rrdir(ast_node, env, root_);
	else if (ast_node->token == T_LEFTHRDC)
		pid = run_heredoc(ast_node, env, root_);
	else
		return (1);
	return (closewait(pid));
}

int	run_redir_inredir(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int	pid;

	if (ast_node->token == T_LEFTRDIR)
		pid = run_ldir_inredir(ast_node, env, root_);
	if (ast_node->token == T_RIGHTRDIR)
		pid = run_rdir_inredir(ast_node, env, root_);
	if (ast_node->token == T_RAPPEND)
		pid = run_rrdir_inredir(ast_node, env, root_);
	if (ast_node->token == T_LEFTHRDC)
		pid = run_heredoc_inredir(ast_node, env, root_);
	return (closewait(pid));
}
