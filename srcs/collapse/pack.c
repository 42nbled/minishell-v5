/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:01:52 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 18:23:39 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fargs	*pack(t_btree *ast_node, t_map **env, t_btree *root_)
{
	t_fargs	*new;
	int		i;

	new = malloc(sizeof(t_fargs));
	new->ast_node = NULL;
	new->env = env;
	new->root_ = root_;
	new->av = NULL;
	new->ac = -1;
	if (ast_node)
		new->ast_node = ast_node;
	else
		return (new);
	if (ast_node->token != T_COMMAND)
		return (new);
	new->av = get_av(ast_node);
	new->ac = 0;
	i = -1;
	if (!new->av)
		return (new);
	while (new->av[++i])
		;
	new->ac = i;
	return (new);
}

void	free_pack(t_fargs *info)
{
	free_map(*(info->env));
	btree_clear(info->root_);
	if (!info->av)
		return ;
	free_ac(info);
	free(info);
}

void	free_ac(t_fargs *info)
{
	int	i;

	i = -1;
	if (!info->av)
		return ;
	while (info->av[++i])
		free(info->av[i]);
	free(info->av);
}
