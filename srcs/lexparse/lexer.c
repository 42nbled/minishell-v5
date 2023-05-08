/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:59:29 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 20:34:51 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	chevron_check(t_list *start, char *str)
{
	int	i;

	i = start->start;
	if (str[i] == '<')
	{
		if (str[i + 1] && str[i + 1] == '<')
			start->token = T_LEFTHRDC;
		else
			start->token = T_LEFTRDIR;
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>')
			start->token = T_RAPPEND;
		else
			start->token = T_RIGHTRDIR;
	}
}

static int	is_env(t_list *start, char *str)
{
	int	i;

	i = 0;
	while (i < start->len)
	{
		if (str[start->start + i++] == '$')
			return (1);
	}
	return (0);
}

void	get_token(t_list *start, char *str)
{
	int	i;

	i = start->start;
	start->token = T_WORD;
	if (!ft_strlen(str) || ft_isspace(str[i]))
		start->token = T_WHITE;
	else if (is_env(start, str))
		start->token = T_ENV;
	else if (str[i] == '\'')
		start->token = T_SQUOTE;
	else if (str[i] == '"')
		start->token = T_DQUOTE;
	else if (str[i] == '|')
		start->token = T_PIPE;
	else if (str[i] == '<' || str[i] == '>')
		chevron_check(start, str);
}
