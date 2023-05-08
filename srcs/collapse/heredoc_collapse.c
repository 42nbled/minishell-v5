/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collapse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:25:51 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 17:41:19 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_delim(t_btree *node)
{
	char	*file;

	file = ft_strdup(((t_list *)node->left->data)->str);
	return (file);
}

int	run_heredoc_inredir(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int		i;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = collapse(ast_node->left, env, root_);
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}	
	return (i);
}

int	collapse_heredoc(t_btree *ast_node, t_map **env, t_btree *root_)
{
	static t_token	last = T_ROOT;
	t_token			temp;
	char			*file;
	char			*delim;
	int				status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!ast_node || ast_node->token == T_COMMAND)
		return (0);
	temp = last;
	last = ast_node->token;
	if (ast_node->token == T_ROOT)
		return (collapse_heredoc(ast_node->left, env, root_));
	if (ast_node->left)
	{
		status = collapse_heredoc(ast_node->left, env, root_);
		if (status)
			return (status);
	}
	if (ast_node->right)
	{
		status = collapse_heredoc(ast_node->right, env, root_);
		if (status)
			return (status);
	}
	if (ast_node->token == T_LEFTHRDC && temp != T_LEFTHRDC)
	{
		file = heredoc_path();
		delim = get_delim(ast_node->right);
		ast_node->data = ft_lstnew_expand(file, T_ARGS);
		if (!get_one_heredoc(file, delim, pack(NULL, env, root_)))
			return (1);
		return (0);
	}
	else if (ast_node->token == T_LEFTHRDC)
	{
		file = heredoc_path();
		printf("heredoc inheredoc %s\n", file);
		delim = get_delim(ast_node->right);
		ast_node->data = ft_lstnew_expand(file, T_ARGS);
		return (0);
	}
	else if (ast_node->token == T_RIGHTRDIR || ast_node->token == T_RAPPEND)
	{
		int	flags;

		file = get_delim(ast_node->right);
		flags = O_WRONLY | O_CREAT;
		if (ast_node->token == T_RAPPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		close(open(file, flags, 0666));
		free(file);
	}
	else if (ast_node->token == T_LEFTRDIR)
	{
		int	fd;

		file = get_delim(ast_node->right);
		fd = open(file, O_RDONLY, 0666);
		free(file);
		if (fd == -1)
			return (ft_error("open: ", strerror(errno), "", 1));
		close(fd);
	}
	return (0);
}
