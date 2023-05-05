/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:20:21 by nbled             #+#    #+#             */
/*   Updated: 2023/05/05 22:56:27 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last(t_list *tmp)
{
	if (tmp && tmp->token == T_PIPE)
		tmp = tmp->next;
	while (tmp && tmp->token == T_WHITE)
		tmp = tmp->next;
	if (!tmp)
		return (0);
	return (1);
}

int	pipe_check(t_list *tmp)
{
	while (tmp)
	{
		while (tmp && tmp->token == T_WHITE)
			tmp = tmp->next;
		if (tmp && tmp->token == T_PIPE)
			return (0);
		while (tmp && tmp->token != T_PIPE)
			tmp = tmp->next;
		if (tmp && tmp->token == T_PIPE && is_last(tmp) == 0)
			return (0);
		if (tmp && tmp->token == T_PIPE)
			tmp = tmp->next;
	}
	return (1);
}

void	put_error(t_list *tmp)
{
	if (tmp->token == T_LEFTRDIR)
		ft_error("syntax error near unexpected token `", "<", "'", 2);
	else if (tmp->token == T_RIGHTRDIR)
		ft_error("syntax error near unexpected token `", ">", "'", 2);
	else if (tmp->token == T_LEFTHRDC)
		ft_error("syntax error near unexpected token `", "<<", "'", 2);
	else if (tmp->token == T_RAPPEND)
		ft_error("syntax error near unexpected token `", ">>", "'", 2);
}

int	redir_check(t_list *tmp)
{
	t_list	*ptr;

	while (tmp)
	{
		while (tmp && tmp ->token < T_LEFTRDIR)
			tmp = tmp->next;
		if (tmp && tmp->token >= T_LEFTRDIR)
		{
			ptr = tmp;
			tmp = tmp->next;
			while (tmp && tmp->token == T_WHITE)
				tmp = tmp->next;
			if (!tmp || tmp->token >= T_PIPE)
			{
				put_error(ptr);
				return (0);
			}
		}
	}
	return (1);
}

t_list	*lex_check(t_list *start)
{
	if (quote_check(start) == 0)
	{
		ft_lstclear(start);
		last_ret(1, 1);
		return (NULL);
	}
	if (redir_check(start) == 0)
	{
		ft_lstclear(start);
		last_ret(1, 1);
		return (NULL);
	}
	if (pipe_check(start) == 0)
	{
		ft_lstclear(start);
		last_ret(1, 1);
		ft_error("syntax error near unexpected token `", "|", "'", 2);
		return (NULL);
	}
	return (start);
}
