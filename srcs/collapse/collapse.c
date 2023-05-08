/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collapse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:22 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 18:02:01 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
