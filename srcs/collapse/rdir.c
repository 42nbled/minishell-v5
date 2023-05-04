/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:10:16 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 23:42:33 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getfilename(t_btree *node, char *str, t_map **env, t_btree *root_)
{
	t_fargs	*info;
	char	*file;
	t_list	*tmp;

	info = pack(node->right, str, env, root_);
	file = ft_strdup(info->av[0]);
	free_ac(info);
	free(info);
	if (!node->right->right)
		return (file);
	if (!node->left->right)
	{
		node->left->right = btree_new(node->right->right->data, T_ARGS);
		node->right->right->data = NULL;
		return (file);
	}
	tmp = (t_list *)node->left->right->data;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_list *)node->right->right->data;
	node->right->right->data = NULL;
	return (file);
}

int	run_rdir(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	int		i;
	int		fd;
	char	*file;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = 0;
		file = getfilename(ast_node, str, env, root_);
		show_btree(root_, 0, str);
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		free(file);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (ast_node->left)
			rcode = collapse(ast_node->left, str, env, root_);
		free_map(*env);
		btree_clear(root_);
		free(str);
		exit(rcode);
	}	
	return (i);
}

int	run_rrdir(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	int		i;
	int		fd;
	char	*file;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = 0;
		file = getfilename(ast_node, str, env, root_);
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		free(file);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (ast_node->left)
			rcode = collapse(ast_node->left, str, env, root_);
		free_map(*env);
		btree_clear(root_);
		free(str);
		exit(rcode);
	}	
	return (i);
}
