/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_suite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:21:50 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 19:25:07 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_delim(t_btree *node)
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

int	collapse_heredoc_recur(t_btree *ast_node, t_map **env, t_btree *root_,
	int *status)
{
	*status = 0;
	if (ast_node->left)
	{
		*status = collapse_heredoc(ast_node->left, env, root_);
		if (*status)
			return (*status);
	}
	if (ast_node->right)
	{
		*status = collapse_heredoc(ast_node->right, env, root_);
		if (*status)
			return (*status);
	}
	return (*status);
}
