/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:10:16 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 18:41:44 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getfilename(t_btree *node)
{
	char	*file;

	file = ft_strdup(((t_list *)node->left->data)->str);
	return (file);
}

static int	rdirpipe(char *file, int flags, t_fargs *info)
{
	int		fd;
	int		rcode;
	t_btree	*ast_node;
	t_map	**env;
	t_btree	*root_;

	fd = open(file, flags, 0666);
	free(file);
	if (fd == -1)
		return (free_ac(info), free(info),
			ft_error("open: ", strerror(errno), "", 1));
	dup2(fd, STDOUT_FILENO);
	ast_node = info->ast_node;
	env = info->env;
	root_ = info->root_;
	close(fd);
	free_ac(info);
	free(info);
	rcode = collapse(ast_node, env, root_);
	return (rcode);
}

static int	rdirpipe_inredir(char *file, int flags, t_fargs *info)
{
	int			fd;
	int			rcode;
	t_btree		*ast_node;
	t_map		**env;
	t_btree		*root_;

	fd = open(file, flags, 0666);
	free(file);
	if (fd == -1)
		return (free_ac(info), free(info),
			ft_error("open: ", strerror(errno), "", 1));
	ast_node = info->ast_node;
	env = info->env;
	root_ = info->root_;
	close(fd);
	free_ac(info);
	free(info);
	rcode = collapse(ast_node, env, root_);
	return (rcode);
}

int	run_rdir(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int		i;
	char	*file;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = 0;
		file = getfilename(ast_node->right);
		if (ast_node->left)
			rcode = rdirpipe(file, O_WRONLY | O_TRUNC,
					pack(ast_node->left, env, root_));
		else
		{
			free(file);
			close(open(file, O_WRONLY | O_TRUNC, 0666));
		}
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}	
	return (i);
}

int	run_rdir_inredir(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int		i;
	char	*file;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = 0;
		file = getfilename(ast_node->right);
		if (ast_node->left)
			rcode = rdirpipe_inredir(file, O_WRONLY | O_TRUNC,
					pack(ast_node->left, env, root_));
		else
		{
			free(file);
			close(open(file, O_WRONLY | O_TRUNC, 0666));
		}
		free(file);
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}	
	return (i);
}

int	run_rrdir(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int		i;
	char	*file;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = 0;
		file = getfilename(ast_node->right);
		if (ast_node->left)
			rcode = rdirpipe(file, O_WRONLY | O_APPEND,
					pack(ast_node->left, env, root_));
		else
		{
			free(file);
			close(open(file, O_WRONLY | O_APPEND, 0666));
		}
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}	
	return (i);
}

int	run_rrdir_inredir(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int		i;
	char	*file;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = 0;
		file = getfilename(ast_node->right);
		if (ast_node->left)
			rcode = rdirpipe_inredir(file, O_WRONLY | O_APPEND,
					pack(ast_node->left, env, root_));
		else
		{
			free(file);
			close(open(file, O_WRONLY | O_APPEND, 0666));
		}
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}	
	return (i);
}
