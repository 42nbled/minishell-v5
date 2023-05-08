/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:01:18 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 18:03:21 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getfpos(char *left)
{
	int		rvalue;

	if (!left)
		return (-1);
	if (ft_strcmp(left, "echo") == 0)
		rvalue = 1;
	else if (ft_strcmp(left, "cd") == 0)
		rvalue = 2;
	else if (ft_strcmp(left, "pwd") == 0)
		rvalue = 3;
	else if (ft_strcmp(left, "env") == 0)
		rvalue = 4;
	else if (ft_strcmp(left, "exit") == 0)
		rvalue = 5;
	else if (ft_strcmp(left, "unset") == 0)
		rvalue = 6;
	else if (ft_strcmp(left, "export") == 0)
		rvalue = 7;
	else
		rvalue = 0;
	return (rvalue);
}

int	run_command(t_btree *ast_node, t_map **env, t_btree *root_)
{
	t_fargs	*info;
	int		i;

	info = pack(ast_node, env, root_);
	if (!info->ac)
		return (free(info), 0);
	i = getfpos(info->av[0]);
	if (i == 0)
		return (free_ac(info), free(info), f_exec(info));
	if (i == 1)
		return (free_ac(info), free(info), f_echo(info));
	if (i == 2)
		return (free_ac(info), free(info), f_cd(info));
	if (i == 3)
		return (free_ac(info), free(info), f_pwd(info));
	if (i == 4)
		return (free_ac(info), free(info), f_env(info));
	if (i == 5)
		return (free_ac(info), free(info), f_exit(info));
	if (i == 6)
		return (free_ac(info), free(info), f_unset(info));
	if (i == 7)
		return (free_ac(info), free(info), f_export(info));
	return (free_ac(info), free(info), 1);
}

int	run_command_inpipe(t_btree *ast_node, t_map **env, t_btree *root_)
{
	t_fargs	*info;
	int		i;

	info = pack(ast_node, env, root_);
	if (!info->ac)
		return (free(info), 0);
	i = getfpos(info->av[0]);
	if (i == 0)
		return (free_ac(info), free(info), f_exec_inpipe(info));
	if (i == 1)
		return (free_ac(info), free(info), f_echo(info));
	if (i == 2)
		return (free_ac(info), free(info), f_cd(info));
	if (i == 3)
		return (free_ac(info), free(info), f_pwd(info));
	if (i == 4)
		return (free_ac(info), free(info), f_env(info));
	if (i == 5)
		return (free_ac(info), free(info), f_exit(info));
	if (i == 6)
		return (free_ac(info), free(info), f_unset(info));
	if (i == 7)
		return (free_ac(info), free(info), f_export(info));
	return (free_ac(info), free(info), 1);
}
