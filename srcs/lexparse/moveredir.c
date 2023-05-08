/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveredir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:07:13 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 19:11:29 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_stack(t_list **pile_a, t_list **l_start)
{
	t_list	*ptr;

	if (!*pile_a)
		*pile_a = *l_start;
	else
		ft_lstadd_back(pile_a, *l_start);
	ptr = *l_start;
	if ((*l_start)->token > T_PIPE)
	{
		ptr = ptr->next;
		*l_start = (*l_start)->next;
	}
	*l_start = (*l_start)->next;
	ptr->next = NULL;
}

t_list	*ft_moveredir(t_list *l_start)
{
	t_list	*pile_a;
	t_list	*pile_b;
	t_list	*prev;

	prev = NULL;
	while (l_start)
	{
		pile_a = NULL;
		pile_b = NULL;
		while (l_start && l_start->token != T_PIPE)
		{
			if (l_start->token < T_PIPE)
				insert_stack(&pile_a, &l_start);
			else if (l_start->token > T_PIPE)
				insert_stack(&pile_b, &l_start);
		}
		ft_lstadd_back(&pile_a, pile_b);
		while (l_start && l_start->token == T_PIPE)
			insert_stack(&pile_a, &l_start);
		if (!prev)
			prev = pile_a;
		else
			ft_lstadd_back(&prev, pile_a);
	}
	return (prev);
}
