/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:59:01 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 21:32:26 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_av(t_btree *node)
{
	char	**result;
	int		i;
	t_list	*tmp;

	if (!node->left)
		return (NULL);
	i = 0;
	if (!node->right)
	{
		result = malloc(sizeof(char *) * 2);
		result[0] = ft_strdup(((t_list*)node->left->data)->str);
		result[1] = NULL;
		return (result);
	}
	tmp = (t_list*)node->right->data;
	while (tmp && ++i)
		tmp = tmp->next;
	result = malloc(sizeof(char *) * (i + 2));
	result[i = 0] = ft_strdup(((t_list*)node->left->data)->str);
	tmp = (t_list*)node->right->data;
	while (tmp && ++i)
	{
		result[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	result[i + 1] = NULL;
	return (result);
}