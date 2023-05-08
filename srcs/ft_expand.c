/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 23:15:54 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 08:24:08 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_expand_env(t_list *l_start, char *str, t_map **env)
{
	t_list	*ptr;
	t_list	*last;
	char	*word;
	char	**tmp;
	int		i;

	word = ft_substr(str, l_start->start, l_start->len);
	l_start->str = extract_value(word, *env);
	free(word);
	if (!l_start->str || !*l_start->str)
		return (l_start);
	tmp = ft_splitexpand(l_start->str);
	i = -1;
	if (ft_isspace(l_start->str[0]))
		ptr = ft_lstnew_expand(NULL, T_WHITE);
	else
	{
		ptr = ft_lstnew_expand(tmp[++i], T_WORD);
		if (tmp[i + 1])
			ft_lstadd_back(&ptr, ft_lstnew_expand(NULL, T_WHITE));
	}
	while (tmp[++i])
	{
		ft_lstadd_back(&ptr, ft_lstnew_expand(tmp[i], T_WORD));
		if (tmp[i + 1])
			ft_lstadd_back(&ptr, ft_lstnew_expand(NULL, T_WHITE));
	}
	if (ft_isspace(l_start->str[ft_strlen(l_start->str) - 1]))
		ft_lstadd_back(&ptr, ft_lstnew_expand(NULL, T_WHITE));
	last = ft_lstlast(ptr);
	ft_lstlast(ptr)->next = l_start->next;
	l_start->next = ptr;
	free(tmp);
	return (last);
}

t_list	*ft_expand_env_dquote(t_list *l_start, char *str, t_map **env)
{
	char	*word;
	char	*value;
	t_list	*tmp;

	word = ft_substr(str, l_start->start, l_start->len);
	value = extract_value(word, *env);
	tmp = l_start->next;
	l_start->next = ft_lstnew_expand(value, T_WORD);
	l_start->next->next = tmp;
	free(word);
	return (l_start->next);
}

void	ft_expand_word(t_list *tmp, char *str)
{
	int		i;

	i = 0;
	tmp->str = (char *)malloc(tmp->len + 1);
	while (i < tmp->len)
	{
		tmp->str[i] = str[tmp->start + i];
		i++;
	}
	tmp->str[i] = '\0';
}

t_list	*ft_expand(t_list *l_start, char *str, t_map **env)
{
	t_list	*tmp;
	t_list	*swapvar;

	tmp = l_start;
	(void)env;
	while (tmp)
	{
		if (tmp->token == T_SQUOTE)
		{
			if (tmp->next && tmp->token == tmp->next->token)
			{
				swapvar = tmp->next;
				tmp->next = ft_lstnew_expand(NULL, T_WORD);
				tmp->next->next = swapvar;
				tmp = tmp->next;
			}
			tmp = tmp->next;
			while (tmp && tmp->token != T_SQUOTE)
			{
				if (tmp && tmp->token == T_WORD)
					ft_expand_word(tmp, str);
				tmp = tmp->next;
			}
		}
		else if (tmp->token == T_DQUOTE)
		{
			if (tmp->next && tmp->token == tmp->next->token)
			{
				swapvar = tmp->next;
				tmp->next = ft_lstnew_expand(NULL, T_WORD);
				tmp->next->next = swapvar;
				tmp = tmp->next;
			}
			tmp = tmp->next;
			while (tmp && tmp->token != T_DQUOTE)
			{
				if (tmp && tmp->token == T_WORD)
					ft_expand_word(tmp, str);
				else if (tmp && tmp->token == T_ENV)
					tmp = ft_expand_env_dquote(tmp, str, env);
				tmp = tmp->next;
			}
		}
		else if (tmp && tmp->token == T_WORD)
			ft_expand_word(tmp, str);
		else if (tmp && tmp->token == T_ENV)
			tmp = ft_expand_env(tmp, str, env);
		if (tmp)
			tmp = tmp->next;
	}
	return (l_start);
}
