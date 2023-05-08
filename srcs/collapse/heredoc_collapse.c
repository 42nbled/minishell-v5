/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collapse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:25:51 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 22:49:22 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	collapse_heredoc_heredoc(t_btree *ast_node, t_map **env, t_btree *root_)
{
	char			*file;
	char			*delim;

	file = heredoc_path();
	delim = get_delim(ast_node->right);
	ast_node->data = ft_lstnew_expand(file, T_ARGS);
	if (get_one_heredoc(file, delim, pack(NULL, env, root_)))
		return (1);
	return (0);
}

int	collapse_heredoc_heredocchained(t_btree *ast_node, t_map **env,
	t_btree *root_)
{
	char			*file;
	char			*delim;

	(void)env;
	(void)root_;
	file = heredoc_path();
	delim = get_delim(ast_node->right);
	ast_node->data = ft_lstnew_expand(file, T_ARGS);
	return (0);
}

int	preopen(t_btree *ast_node, t_map **env, t_btree *root_)
{
	char	*file;
	int		flags;
	int		fd;

	(void)env;
	(void)root_;
	file = get_delim(ast_node->right);
	flags = O_WRONLY | O_CREAT;
	if (ast_node->token == T_RAPPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0666);
	free(file);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), "", 1));
	return (0);
}

int	precheckfile(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int		fd;
	char	*file;

	(void)env;
	(void)root_;
	file = get_delim(ast_node->right);
	fd = open(file, O_RDONLY, 0666);
	free(file);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), "", 1));
	close(fd);
	return (0);
}

int	collapse_heredoc(t_btree *ast_node, t_map **env, t_btree *root_)
{
	static t_token	last = T_ROOT;
	t_token			temp;
	int				status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!ast_node || ast_node->token == T_COMMAND)
		return (0);
	temp = last;
	last = ast_node->token;
	if (ast_node->token == T_ROOT)
		return (collapse_heredoc(ast_node->left, env, root_));
	else if (collapse_heredoc_recur(ast_node, env, root_, &status) && status)
		return (status);
	if (ast_node->token == T_LEFTHRDC && temp != T_LEFTHRDC)
		return (collapse_heredoc_heredoc(ast_node, env, root_));
	else if (ast_node->token == T_LEFTHRDC)
		return (collapse_heredoc_heredocchained(ast_node, env, root_));
	else if (ast_node->token == T_RIGHTRDIR || ast_node->token == T_RAPPEND)
		return (preopen(ast_node, env, root_));
	else if (ast_node->token == T_LEFTRDIR)
		return (precheckfile(ast_node, env, root_));
	return (0);
}
