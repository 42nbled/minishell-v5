/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:01:18 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 19:15:33 by cde-sede         ###   ########.fr       */
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
		i = f_exec(info);
	else if (i == 1)
		i = f_echo(info);
	else if (i == 2)
		i = f_cd(info);
	else if (i == 3)
		i = f_pwd(info);
	else if (i == 4)
		i = f_env(info);
	else if (i == 5)
		i = f_exit(info);
	else if (i == 6)
		i = f_unset(info);
	else if (i == 7)
		i = f_export(info);
	return (free_ac(info), free(info), i);
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
		i = f_exec_inpipe(info);
	else if (i == 1)
		i = f_echo(info);
	else if (i == 2)
		i = f_cd(info);
	else if (i == 3)
		i = f_pwd(info);
	else if (i == 4)
		i = f_env(info);
	else if (i == 5)
		i = f_exit(info);
	else if (i == 6)
		i = f_unset(info);
	else if (i == 7)
		i = f_export(info);
	return (free_ac(info), free(info), i);
}
