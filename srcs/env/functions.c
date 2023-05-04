/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:44:32 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 19:18:56 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env(char *key, char *value, t_map *env)
{
	t_map	*e;
	t_map	*prev;

	if (!key || ft_strlen(key) == 0)
		return (1);
	e = env;
	while (e != NULL && ft_strcmp(e->key, key))
	{
		prev = e;
		e = e->next;
	}
	if (e == NULL)
		prev->next = map_new(key, value);
	else
	{
		free(e->value);
		e->value = ft_strdup(value);
	}
	return (0);
}

char	*get_env(char *key, t_map *env)
{
	t_map	*e;

	e = env;
	if (!key || ft_strlen(key) == 0)
		return (NULL);
	while (e != NULL && ft_strcmp(e->key, key))
	{
		e = e->next;
	}
	if (e == NULL)
		return (NULL);
	return (e->value);
}

void	show_env(t_map *env)
{
	t_map	*e;

	e = env;
	while (e)
	{
		printf("%s=%s\n", e->key, e->value);
		e = e->next;
	}
}
