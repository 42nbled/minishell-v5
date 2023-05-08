/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:27:50 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 01:43:50 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dellink(char *key, t_map **env)
{
	t_map	*tmp;
	t_map	*prev;

	tmp = *env;
	prev = NULL;
	if (tmp != NULL && !ft_strcmp(tmp->key, key))
	{
		*env = tmp->next;
		envfreeone(tmp);
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->key, key))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	if (prev)
		prev->next = tmp->next;
	envfreeone(tmp);
}

int	f_unset(t_fargs *info)
{
	int	i;

	i = 0;
	while (++i < info->ac)
	{
		if (get_env(info->av[i], *(info->env)))
			dellink(info->av[i], info->env);
	}
	return (0);
}
