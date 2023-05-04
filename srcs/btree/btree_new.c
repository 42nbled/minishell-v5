/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:17:21 by nbled             #+#    #+#             */
/*   Updated: 2023/03/28 19:53:28 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*btree_new(void *data, int token)
{
	t_btree	*n;

	n = malloc(sizeof(t_btree));
	if (!n)
		return (NULL);
	n->token = token;
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	return (n);
}
