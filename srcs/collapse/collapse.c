/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collapse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:22 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 21:29:40 by cde-sede         ###   ########.fr       */
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

t_fargs	*pack(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	t_fargs	*new;
	int		i;

	new = malloc(sizeof(t_fargs));
	new->ast_node = ast_node;
	new->str = str;
	new->env = env;
	new->root_ = root_;
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
	free(info->str);
	if (!info->av)
		return ;
	free_ac(info);
	free(info);
}

void	free_ac(t_fargs *info)
{
	int	i;

	i = -1;
	while (info->av[++i])
		free(info->av[i]);
	free(info->av);
}

int	run_command(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	t_fargs	*info;
	int		i;
	int		e;

	e = 1;
	info = pack(ast_node, str, env, root_);
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

int	run_command_inpipe(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	t_fargs	*info;
	int		i;
	int		e;

	e = 1;
	info = pack(ast_node, str, env, root_);
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

int	collapse(t_btree *root, char *str, t_map **env, t_btree *root_)
{
	int	e;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (root->token == T_ROOT)
		return (collapse(root->left, str, env, root_));
	else if (root->token == T_COMMAND)
		return (run_command(root, str, env, root_));
	else if (root->token == T_PIPE)
		return (run_pipe(root, str, env, root_));
	else if (root->token >= T_LEFTRDIR && root->token <= T_RAPPEND)
		return (run_redir(root, str, env, root_));
	else
		return (ft_error("Parsing exception?", "", "", 1));
	return (e);
}

int	collapse_inpipe(t_btree *root, char *str, t_map **env, t_btree *root_)
{
	int	e;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (root->token == T_COMMAND)
		return (run_command_inpipe(root, str, env, root_));
	else if (root->token == T_PIPE)
		return (run_pipe(root, str, env, root_));
	else if (root->token >= T_LEFTRDIR && root->token <= T_RAPPEND)
		return (run_redir(root, str, env, root_));
	else
		return (ft_error("Parsing exception?", "", "", 1));
	return (e);
}
