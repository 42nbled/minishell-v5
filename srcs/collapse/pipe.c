/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:54:24 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/07 20:54:04 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	leftpipe(t_btree *ast_node, int *pipes,
	t_map **env, t_btree *root_)
{
	int	i;
	int	rcode;

	i = fork();
	if (i == 0)
	{
		close(STDOUT_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		close(pipes[1]);
		rcode = (collapse(ast_node->left, env, root_));
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}
	return (i);
}

static int	rightpipe(t_btree *ast_node, int *pipes,
	t_map **env, t_btree *root_)
{
	int	i;
	int	rcode;

	i = fork();
	if (i == 0)
	{
		close(STDIN_FILENO);
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		close(pipes[0]);
		rcode = (collapse(ast_node->right, env, root_));
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}
	return (i);
}

static int	check_sig(int status)
{
	if (WIFEXITED(status))
		if (WEXITSTATUS(status))
			return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (131);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
		return (ft_error("segmentation fault", "", "", 139));
	return (0);
}

static int	closewait(int *pipes, int *pid)
{
	int	left_status;
	int	right_status;

	close(pipes[0]);
	close(pipes[1]);
	if (waitpid(pid[0], &left_status, 0) == -1)
		return (1);
	if (waitpid(pid[1], &right_status, 0) == -1)
		return (1);
	if (check_sig(left_status))
		return (check_sig(left_status));
	if (check_sig(right_status))
		return (check_sig(right_status));
	return (0);
}

int	run_pipe(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int	pipes[2];
	int	child[2];

	if (pipe(pipes) == -1)
		return (2);
	if (!ast_node->left)
		return (3);
	child[0] = leftpipe(ast_node, pipes, env, root_);
	child[1] = rightpipe(ast_node, pipes, env, root_);
	return (closewait(pipes, child));
}
