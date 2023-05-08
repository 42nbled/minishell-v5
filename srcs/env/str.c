/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:59:01 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 04:16:12 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **no_right(t_btree *node)
{
	char	**result;

	result = malloc(sizeof(char *) * 2);
	if (((t_list*)node->left->data)->str)
		result[0] = ft_strdup(((t_list*)node->left->data)->str);
	else
		result[0] = ft_strdup("");
	result[1] = NULL;
	return (result);
}

char	**get_av(t_btree *node)
{
	char	**result;
	int		i;
	t_list	*tmp;

	if (!node->left)
		return (NULL);
	i = 0;
	if (!node->right)
		return (no_right(node));
	tmp = (t_list*)node->right->data;
	while (tmp && ++i)
		tmp = tmp->next;
	result = malloc(sizeof(char *) * (i + 2));
	result[i = 0] = ft_strdup(((t_list*)node->left->data)->str);
	tmp = (t_list*)node->right->data;
	while (tmp && ++i)
	{
		if (tmp->str)
			result[i] = ft_strdup(tmp->str);
		else
			result[i] = ft_strdup("");
		tmp = tmp->next;
	}
	result[i + 1] = NULL;
	return (result);
}
