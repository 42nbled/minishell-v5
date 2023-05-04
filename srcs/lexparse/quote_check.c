/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 06:54:13 by nbled             #+#    #+#             */
/*   Updated: 2023/05/02 09:53:18 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	squote_check(t_list *start)
{
	t_list	*tmp;

	tmp = start->next;
	while (tmp && tmp->token != T_SQUOTE)
	{
		tmp->token = T_WORD;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_error("syntax error near unexpected token `", "'", "'", 2);
		return (0);
	}
	return (1);
}

static int	dquote_check(t_list *start)
{
	t_list	*tmp;

	tmp = start->next;
	while (tmp && tmp->token != T_DQUOTE)
	{
		if (tmp->token != T_ENV)
			tmp->token = T_WORD;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_error("syntax error near unexpected token `", "\"", "'", 2);
		return (0);
	}
	return (1);
}

int	quote_check(t_list *tmp)
{
	while (tmp)
	{
		if (tmp->token == T_SQUOTE)
		{
			if (!squote_check(tmp))
				return (0);
			tmp = tmp->next;
			while (tmp && tmp->token != T_SQUOTE)
				tmp = tmp->next;
		}
		else if (tmp->token == T_DQUOTE)
		{
			if (!dquote_check(tmp))
				return (0);
			tmp = tmp->next;
			while (tmp && tmp->token != T_DQUOTE)
				tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}
