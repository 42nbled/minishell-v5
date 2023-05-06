/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 05:20:45 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/07 00:16:42 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getpwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	return (cwd);
}

char	**default_environ(void)
{
	char	**environ;
	char	*cwd;

	cwd = getpwd();
	if (!cwd)
		return (NULL);
	environ = malloc(sizeof(char *) * 3);
	if (!environ)
		return (NULL);
	environ[0] = ft_strjoin("PWD=", cwd);
	environ[1] = ft_strjoin("SHLVL=", "0");
	environ[2] = NULL;
	free(cwd);
	return (environ);
}

t_map	*envcopy(t_map *base)
{
	t_map	*first;
	t_map	*tmp;
	t_map	*e;

	first = NULL;
	e = NULL;
	while (base)
	{
		tmp = map_new(base->key, base->value);
		if (!tmp)
			return (NULL);
		if (!first)
		{
			first = tmp;
			e = tmp;
		}
		else
		{
			e->next = tmp;
			e = tmp;
		}
		base = base->next;
	}
	return (first);
}

void	sort_env(t_map *lst)
{
	t_map	*cmp;

	cmp = lst;
	while (lst)
	{
		if (lst->next)
			cmp = lst->next;
		while (cmp)
		{
			if (ft_strcmp(lst->key, cmp->key) > 0)
			{
				ft_swap_str(&lst->key, &cmp->key);
				ft_swap_str(&lst->value, &cmp->value);
			}
			cmp = cmp->next;
		}
		lst = lst->next;
	}
}
