/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:13:28 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 20:13:05 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_expand_env_part2(t_list *l_start, char **tmp, t_list *ptr, int i)
{
	t_list	*last;

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

t_list	*ft_expand_env(t_list *l_start, char *str, t_map **env)
{
	t_list	*ptr;
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
	return (ft_expand_env_part2(l_start, tmp, ptr, i));
}
