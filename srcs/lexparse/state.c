/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:33:22 by nbled             #+#    #+#             */
/*   Updated: 2023/05/03 18:01:17 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*state_command_right(t_list *l_start, t_btree *ast_node)
{
	t_list	*tmp;
	t_list	*ptr;

	tmp = l_start;
	ast_node->right = btree_new(NULL, T_COMMAND);
	ast_node->right->left = btree_new(tmp, T_FUNCTION);
	ptr = tmp;
	tmp = tmp->next;
	ptr->next = NULL;
	ptr = NULL;
	if (tmp && tmp->token < T_PIPE)
	{
		ast_node->right->right = btree_new(tmp, T_ARGS);
		while (tmp && tmp->next && tmp->next->token < T_PIPE)
			tmp = tmp->next;
		if (tmp)
		{
			ptr = tmp->next;
			tmp->next = NULL;
		}
	}
	else if (tmp)
	{
		ast_node->right->right = btree_new(NULL, T_ARGS);
		return (tmp);
	}
	return (ptr);
}

t_list	*state_command(t_list *l_start, t_btree *ast_node)
{
	t_list	*tmp;
	t_list	*ptr;

	tmp = l_start;
	ast_node->left = btree_new(NULL, T_COMMAND);
	ast_node->left->left = btree_new(tmp, T_FUNCTION);
	ptr = tmp;
	tmp = tmp->next;
	ptr->next = NULL;
	ptr = NULL;
	if (tmp && tmp->token < T_PIPE)
	{
		ast_node->left->right = btree_new(tmp, T_ARGS);
		while (tmp && tmp->next && tmp->next->token < T_PIPE)
			tmp = tmp->next;
		if (tmp)
		{
			ptr = tmp->next;
			tmp->next = NULL;
		}
	}
	else if (tmp)
	{
		ast_node->left->right = btree_new(NULL, T_ARGS);
		return (tmp);
	}
	return (ptr);
}

t_list	*state_pipe(t_list *l_start, t_btree *ast_node)
{
	t_btree	*pipe;
	t_list	*tmp;

	tmp = l_start;
	pipe = btree_new(NULL, l_start->token);
	pipe->left = ast_node->left;
	ast_node->left = pipe;
	l_start = l_start->next;
	free(tmp);
	while (l_start && l_start->token == T_WHITE)
	{
		tmp = l_start;
		l_start = l_start->next;
		free(tmp);
	}
	if (l_start && l_start->token < T_PIPE)
	{
		return (state_command_right(l_start, pipe));
	}
	return (l_start);
}

// a > b c

// root
// 	rdir
// 		command
// 			a
// 			c
// 		args
// 			b

// > b c

// b="test kkchose"

// root
// 	rdir
// 		command
// 			c
// 		args
// 			$b

// root
// 	rdir
// 		command
// 			kkchose c
// 		args
// 			test

/*

a | b > c

root
	pipe
		command
			fonction a 
		rdir
			command 
				fonction b
			c

 a | b > c > d

 root
	pipe
		command
			fonction a
		rdir
			rdir
				b
				c
			d
*/

t_base_result	state_base(t_list *l_start, t_btree *ast_node)
{
	t_list			*tmp;
	t_base_result	result;

	tmp = l_start;
	result.status = T_OK;
	result.lst = NULL;
	while (tmp)
	{
		if (tmp->token < T_PIPE)
			tmp = state_command(tmp, ast_node);
		else if (tmp->token >= T_PIPE && tmp->token < T_LPAREN)
			tmp = state_pipe(tmp, ast_node);
	}
	return (result);
}
