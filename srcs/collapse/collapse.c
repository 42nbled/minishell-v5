/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collapse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:22 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 06:59:06 by cde-sede         ###   ########.fr       */
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

int	run_command(t_btree *ast_node, t_map **env, t_btree *root_)
{
	t_fargs	*info;
	int		i;
	int		e;

	e = 1;
	info = pack(ast_node, env, root_);
	if (!info->ac)
	{
		free(info);
		return (0);
	}
	i = getfpos(info->av[0]);
	if (i == 0)
		e = f_exec(info);
	if (i == 1)
		e = f_echo(info);
	if (i == 2)
		e = f_cd(info);
	if (i == 3)
		e = f_pwd(info);
	if (i == 4)
		e = f_env(info);
	if (i == 5)
		e = f_exit(info);
	if (i == 6)
		e = f_unset(info);
	if (i == 7)
		e = f_export(info);
	free_ac(info);
	free(info);
	return (e);
}

int	run_command_inpipe(t_btree *ast_node, t_map **env, t_btree *root_)
{
	t_fargs	*info;
	int		i;
	int		e;

	e = 1;
	info = pack(ast_node, env, root_);
	if (!info->ac)
	{
		free(info);
		return (0);
	}
	i = getfpos(info->av[0]);
	if (i == 0)
		e = f_exec_inpipe(info);
	if (i == 1)
		e = f_echo(info);
	if (i == 2)
		e = f_cd(info);
	if (i == 3)
		e = f_pwd(info);
	if (i == 4)
		e = f_env(info);
	if (i == 5)
		e = f_exit(info);
	if (i == 6)
		e = f_unset(info);
	if (i == 7)
		e = f_export(info);
	free_ac(info);
	free(info);
	return (e);
}

int	collapse(t_btree *root, t_map **env, t_btree *root_)
{
	static t_token	last = T_ROOT;

	if (!root)
		return (0);
	if (root->token == T_ROOT)
		return (last = T_ROOT, collapse(root->left, env, root_));
	else if (root->token == T_COMMAND && last != T_ROOT)
		return (run_command_inpipe(root, env, root_));
	else if (root->token == T_COMMAND)
		return (run_command(root, env, root_));
	else if (root->token == T_PIPE)
		return (last = S_PIPE, run_pipe(root, env, root_));
	else if (root->token >= T_LEFTRDIR && root->token <= T_RAPPEND)
		return (run_redir(root, env, root_, &last));
	else
		return (ft_error("Parsing exception?", "", "", 1));
}
