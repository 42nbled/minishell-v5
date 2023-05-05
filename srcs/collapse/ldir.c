/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:35:43 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 23:43:52 by cde-sede         ###   ########.fr       */
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

static int	ldirpipe(char *file, t_fargs *info)
{
	int	fd;
	int	rcode;

	fd = open(file, O_RDONLY, 0666);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), "", 1));
	dup2(fd, STDIN_FILENO);
	rcode = collapse_inpipe(info->ast_node, info->str, info->env, info->root_);
	free_ac(info);
	free(info);
	return (rcode);
}

int	run_ldir(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	int		i;
	char	*file;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = 0;
		file = getfilename(ast_node, str, env, root_);
		printf("filename: %s\n", file);
		if (ast_node->left)
			rcode = ldirpipe(file, pack(ast_node->left, str, env, root_));
		free(file);
		free_map(*env);
		btree_clear(root_);
		free(str);
		exit(rcode);
	}	
	return (i);
}
