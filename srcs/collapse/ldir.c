/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:35:43 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 06:19:45 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getfilename(t_btree *node)
{
	char	*file;

	file = ft_strdup(((t_list*)node->left->data)->str);
	return (file);
}

static int	ldirpipe(char *file, t_fargs *info)
{
	int	fd;
	int	rcode;

	fd = open(file, O_RDONLY, 0666);
	if (fd == -1)
		return (free_ac(info), free(info), ft_error("open: ", strerror(errno), "", 1));
	dup2(fd, STDIN_FILENO);
	close(fd);
	rcode = collapse(info->ast_node, info->env, info->root_);
	free_ac(info);
	free(info);
	return (rcode);
}

int	run_ldir(t_btree *ast_node, t_map **env, t_btree *root_)
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
			rcode = ldirpipe(file, pack(ast_node->left, env, root_));
		free(file);
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}	
	return (i);
}

static int	ldirpipe_inredir(char *file, t_fargs *info)
{
	int	fd;
	int	rcode;

	fd = open(file, O_RDONLY, 0666);
	if (fd == -1)
		return (free_ac(info), free(info), ft_error("open: ", strerror(errno), "", 1));
	close(fd);
	rcode = collapse(info->ast_node, info->env, info->root_);
	free_ac(info);
	free(info);
	return (rcode);
}

int	run_ldir_inredir(t_btree *ast_node, t_map **env, t_btree *root_)
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
			rcode = ldirpipe_inredir(file, pack(ast_node->left, env, root_));
		free(file);
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}	
	return (i);
}

