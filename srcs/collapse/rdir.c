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
	char	*file;
	t_fargs	*info;

	info = pack(node->right, str, env, root_);
	file = ft_strdup(info->av[info->ac - 1]);
	free_ac(info);
	free(info);
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
		ft_putstr_fd("rdir ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		free(file);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (ast_node->left)
			rcode = collapse_inpipe(ast_node->left, str, env, root_);
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
			rcode = collapse_inpipe(ast_node->left, str, env, root_);
		free_map(*env);
		btree_clear(root_);
		free(str);
		exit(rcode);
	}	
	return (i);
}
