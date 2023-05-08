/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:31:42 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 01:28:02 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envfreeone(t_map *e)
{
	free(e->key);
	free(e->value);
	free(e);
}

void	free_map(t_map	*e)
{
	if (e)
	{
		if (e->next)
			free_map(e->next);
		envfreeone(e);
	}
}

// static void	free_environ(char **e)
// {
// 	int		i;
// 
// 	i = -1;
// 	while (e[++i])
// 		free(e[i]);
// 	free(e);
// }

char	**export(t_map *e)
{
	t_map	*n;
	char	**r;
	int		i;

	i = 0;
	n = e;
	r = NULL;
	while (n)
	{
		if (!r)
			r = malloc(sizeof(char *) * 2);
		else
			r = ft_realloc(r, sizeof(char *) * (i + 1),
					sizeof(char *) * (i + 2));
		r[i++] = ft_jointhree(n->key, "=", n->value);
		n = n->next;
	}
	if (r)
		r[i] = NULL;
	return (r);
}
