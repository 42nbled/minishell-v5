/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:48:01 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 19:26:10 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_key(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '$' && str[1] == '?')
		return (2);
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (-1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (!(str[i] && (ft_isalnum(str[i]) || str[i] == '_')))
		i--;
	return (i);
}

char	*extract_value(char *s, t_map *env)
{
	int		delim;
	char	*key;
	char	*value;
	char	*tmp;

	delim = extract_key(s);
	if (delim <= 0)
		return (ft_strdup("$"));
	if (delim == 2)
		value = ft_itoa(last_ret(0, 0));
	else
	{
		key = ft_substr(s, 1, delim++);
		value = ft_strdup(get_env(key, env));
		free(key);
	}
	if (!value)
		return (ft_strdup(s + delim));
	tmp = ft_strjoin(value, s + delim);
	free(value);
	return (tmp);
}
