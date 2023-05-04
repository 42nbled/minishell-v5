/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:43:26 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/23 12:29:53 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*load_env(char **e)
{
	t_map	*start;
	t_map	*tmp;
	t_map	*current;
	int		i;

	start = NULL;
	current = NULL;
	i = -1;
	while (e[++i])
	{
		tmp = map_fromstring(e[i]);
		if (!tmp)
			return (start);
		if (!current)
			current = tmp;
		else
		{
			current->next = tmp;
			current = current->next;
		}
		if (!start)
			start = tmp;
	}
	return (start);
}

t_map	*map_new(char *key, char *value)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->key = malloc(sizeof(char) * (ft_strlen(key) + 1));
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	new->value = NULL;
	if (!value)
		return (new);
	ft_strlcpy(new->key, key, ft_strlen(key) + 1);
	new->value = malloc(sizeof(char) * (ft_strlen(value) + 1));
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	ft_strlcpy(new->value, value, ft_strlen(value) + 1);
	new->next = NULL;
	return (new);
}

int	env_delim(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '=')
			return (i);
	return (-1);
}

int	env_split(char *s, char **key, char **value)
{
	int		n;

	n = env_delim(s);
	if (n == -1)
		return (1);
	*key = malloc(sizeof(char) * (n + 1));
	if (!*key)
		return (1);
	ft_strlcpy(*key, s, n + 1);
	*value = malloc(sizeof(char) * (ft_strlen(s) - n));
	if (!*value)
	{
		free(*key);
		return (1);
	}
	ft_strlcpy(*value, s + n + 1, ft_strlen(s) - n);
	return (0);
}

t_map	*map_fromstring(char *s)
{
	t_map	*m;
	char	*key;
	char	*value;

	if (env_split(s, &key, &value))
		return (NULL);
	m = map_new(key, value);
	free(key);
	free(value);
	return (m);
}
