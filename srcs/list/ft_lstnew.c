/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:19:08 by nbled             #+#    #+#             */
/*   Updated: 2023/05/04 16:14:32 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(int start, int len, char *str)
{
	t_list	*n;

	n = malloc(sizeof(t_list));
	if (!n)
		return (NULL);
	n->start = start;
	n->len = len - start + 1;
	n->str = NULL;
	get_token(n, str);
	n->next = NULL;
	return (n);
}

t_list	*ft_lstnew_expand(char *str, t_token t)
{
	t_list	*n;

	n = malloc(sizeof(t_list));
	if (!n)
		return (NULL);
	n->start = -1;
	n->len = -1;
	n->str = str;
	n->token = t;
	n->next = NULL;
	return (n);
}
