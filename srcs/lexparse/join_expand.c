/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:30:23 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 17:23:53 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_joindeletesuite(t_list **l_start, t_token expected, t_list *ptr)
{
	t_list	*tmp;

	tmp = *l_start;
	while (ptr)
	{
		if (ptr->token == expected)
		{
			tmp->next = ptr->next;
			if (ptr->str)
				free(ptr->str);
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

void	ft_joindelete(t_list **l_start, t_token expected)
{
	t_list	*ptr;

	ptr = (*l_start)->next;
	if ((*l_start)->token == expected)
	{
		if ((*l_start)->str)
			free((*l_start)->str);
		free(*l_start);
		*l_start = ptr;
		if (ptr->next)
			ptr = ptr->next;
	}
	ft_joindeletesuite(l_start, expected, ptr);
}


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

void	ft_joinjoin(t_list *l_start)
{
	t_list	*ptr;
	char	*tmp;

	ptr = l_start->next;
	while (l_start && l_start->next)
	{
		if (ptr->token == T_WORD && l_start->token == T_WORD)
		{
			if (ptr->str)
				tmp = ft_strjoin(l_start->str, ptr->str);
			else
				tmp = ft_strdup(l_start->str);
			free(l_start->str);
			l_start->str = tmp;
			l_start->next = ptr->next;
			if (ptr->str)
				free(ptr->str);
			free(ptr);
			ptr = l_start->next;
		}
		else if (ptr)
		{
			ptr = ptr->next;
			l_start = l_start->next;
		}
	}
}

t_list	*ft_expand_join(t_list **l_start)
{
//	printf("\n----------base\n");
//	print_list(*l_start, str);
//	ft_joindelete(l_start, T_SQUOTE);
//	printf("\n----------squote\n");
//	print_list(*l_start, str);
//	ft_joindelete(l_start, T_DQUOTE);
//	printf("\n----------dquote\n");
//	print_list(*l_start, str);
//	ft_joindelete(l_start, T_ENV);
//	printf("\n----------env\n");
//	print_list(*l_start, str);
//	ft_joinjoin(*l_start);
//	printf("\n----------join\n");
//	print_list(*l_start, str);
//	ft_joindelete(l_start, T_WHITE);
//	printf("\n----------white\n");
//	print_list(*l_start, str);

	ft_joindelete(l_start, T_SQUOTE);
	ft_joindelete(l_start, T_DQUOTE);
	ft_joindelete(l_start, T_ENV);
	ft_joinjoin(*l_start);
	ft_joindelete(l_start, T_WHITE);

	return (ft_moveredir(*l_start));
}
