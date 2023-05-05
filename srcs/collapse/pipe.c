/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:54:24 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 20:27:51 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	leftpipe(t_btree *ast_node, char *str, int *pipes,
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
		rcode = (collapse_inpipe(ast_node->left, str, env, root_));
		free_map(*env);
		btree_clear(root_);
		free(str);
		exit(rcode);
	}
	return (i);
}

static int	rightpipe(t_btree *ast_node, char *str, int *pipes,
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
		rcode = (collapse_inpipe(ast_node->right, str, env, root_));
		free_map(*env);
		btree_clear(root_);
		free(str);
		exit(rcode);
	}
	return (i);
}

static int	closewait(int *pipes, int *pid)
{
	int	left_status;
	int	right_status;

	close(pipes[0]);
	close(pipes[0]);
	if (waitpid(pid[0], &left_status, 0) == -1)
		return (1);
	if (waitpid(pid[0], &right_status, 0) == -1)
		return (1);
		// Clear here using macros, WIFEXITED and WEXITSTATUS
	if (WIFEXITED(left_status))
		if (WEXITSTATUS(left_status))
			return (WEXITSTATUS(left_status));
	if (WIFSIGNALED(left_status) && WTERMSIG(left_status) == SIGINT)
		return (130);
	if (WIFSIGNALED(right_status) && WTERMSIG(right_status) == SIGINT)
		return (130);
	if (WIFSIGNALED(left_status) && WTERMSIG(left_status) == SIGQUIT)
		return (131);
	if (WIFSIGNALED(right_status) && WTERMSIG(right_status) == SIGQUIT)
		return (131);
	if (WIFSIGNALED(left_status) && WTERMSIG(left_status) == SIGSEGV)
		return (ft_error("segmentation fault", "", "", 139));
	if (WIFSIGNALED(right_status) && WTERMSIG(right_status) == SIGSEGV)
		return (ft_error("segmentation fault", "", "", 139));
	if (WIFEXITED(right_status))
		if (WEXITSTATUS(right_status))
			return (WEXITSTATUS(right_status));
	return (0);
}

int	run_pipe(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	int	pipes[2];
	int	child[2];

	if (pipe(pipes) == -1)
		return (2);
	if (!ast_node->left)
		return (3);
	child[0] = leftpipe(ast_node, str, pipes, env, root_);
	child[1] = rightpipe(ast_node, str, pipes, env, root_);
	return (closewait(pipes, child));
}
