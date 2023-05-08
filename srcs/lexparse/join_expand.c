/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:30:23 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 08:13:13 by cde-sede         ###   ########.fr       */
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
		if ((*l_start)->str)
			free((*l_start)->str);
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

/*
void	ft_moveredir(t_list *l_start, char *str)
{
	t_list	*ptr;
	t_list	*end;
	t_list	*tmp;

	(void)str;
	ptr = l_start->next;
	while (ptr)
	{
		if (ptr->token >= T_LEFTRDIR)
		{
			end = ptr->next->next;
			while (end && end->token >= T_LEFTRDIR)
				end = end->next->next;
			if (!end || end == NULL)
				return ;
			l_start->next = end;
			tmp = ptr;
			while (tmp && tmp->next != end)
				tmp = tmp->next;
			tmp->next = end->next;
			end->next = ptr;
			//return;
		}
		l_start = ptr;
		ptr = ptr->next;
		//print_list(l_start, str);
		//printf("\n");
	}
}*/

t_list	*ft_moveredir(t_list *l_start)
{
	t_list	*pile_a;
	t_list	*pile_b;
	t_list	*ptr;
	t_list	*prev;

	prev = NULL;
	while (l_start)
	{
		pile_a = NULL;
		pile_b = NULL;
		while (l_start && l_start->token != T_PIPE)
		{
			if (l_start->token < T_PIPE)
			{
				if (!pile_a)
					pile_a = l_start;
				else
					ft_lstadd_back(&pile_a, l_start);
				ptr = l_start;
				l_start = l_start->next;
				ptr->next = NULL;
			}
			else if (l_start->token > T_PIPE)
			{
				if (!pile_b)
					pile_b = l_start;
				else
					ft_lstadd_back(&pile_b, l_start);
				ptr = l_start->next;
				l_start = l_start->next->next;
				ptr->next = NULL;
			}
		}
		ft_lstadd_back(&pile_a, pile_b);
		ft_lstadd_back(&pile_b, l_start);
		if (l_start && l_start->token == T_PIPE)
		{
			ptr = l_start;
			ft_lstadd_back(&pile_a, l_start);
			l_start = l_start->next;
			ptr->next = NULL;
			prev = pile_a;
		}
		if (prev)
			ft_lstadd_back(&pile_a, l_start);
		else
			prev = pile_a;
	}
	return (prev);
}

/*
			  a
	l_start = > c b
	pile_a  = a
	pile_b  =
	ptr     = a

	a > c b
*/

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

t_list	*ft_expand_join(t_list **l_start, char *str)
{
	(void)str;
	ft_joindelete(l_start, T_SQUOTE);
	ft_joindelete(l_start, T_DQUOTE);
	ft_joindelete(l_start, T_ENV);
	ft_joinjoin(*l_start);
	ft_joindelete(l_start, T_WHITE);
	return (ft_moveredir(*l_start));
}
