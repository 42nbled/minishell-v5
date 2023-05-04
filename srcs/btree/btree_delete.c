/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:17:34 by nbled             #+#    #+#             */
/*   Updated: 2023/03/28 19:54:54 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	btree_clear(t_btree *root)
{
	if (root->left)
		btree_clear(root->left);
	if (root->right)
		btree_clear(root->right);
	if (root->data)
	{
		if (root->token == T_COMMAND
			|| root->token == T_PIPE)
		{
			if (root->data)
				free((char *)root->data);
		}
		else
			ft_lstclear((t_list *)root->data);
	}
	free(root);
}
