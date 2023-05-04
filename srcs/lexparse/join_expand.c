/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:30:23 by nbled             #+#    #+#             */
/*   Updated: 2023/05/04 16:34:08 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_joindelete(t_list **l_start, t_token expected)
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = (*l_start)->next;
	if ((*l_start)->token == expected)
	{
		free(*l_start);
		*l_start = ptr;
		if (ptr->next)
			ptr = ptr->next;
	}
	tmp = *l_start;
	while (ptr)
	{
		if (ptr->token == expected)
		{
			tmp->next = ptr->next;
			free(ptr);
			ptr = tmp->next;
		}
		else if (ptr)
		{
			ptr = ptr->next;
			tmp = tmp->next;
		}
	}
}

void	ft_joinjoin(t_list *l_start)
{
	t_list	*ptr;

	ptr = l_start->next;
	while (l_start && l_start->next)
	{
		if (ptr->token == T_WORD && l_start->token == T_WORD)
		{
			l_start->str = ft_strjoin(l_start->str, ptr->str);
			l_start->next = ptr->next;
			ptr = ptr->next;
		}
		else if (ptr)
		{
			ptr = ptr->next;
			l_start = l_start->next;
		}
	}
}

void	ft_expand_join(t_list **l_start)
{
	ft_joindelete(l_start, T_SQUOTE);
	ft_joindelete(l_start, T_DQUOTE);
	ft_joindelete(l_start, T_ENV);
	ft_joinjoin(*l_start);
	ft_joindelete(l_start, T_WHITE);
}
