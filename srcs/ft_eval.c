/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:34:55 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 22:42:09 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*ft_parse(t_list *l_start)
{
	t_btree			*root;
	t_base_result	result;

	root = btree_new(NULL, T_ROOT);
	if (l_start && l_start->token == T_WHITE)
		l_start = l_start->next;
	result = state_base(l_start, root);
	if (result.status == T_ERROR)
	{
		printf("Invalid syntax.\n");
		btree_clear(root);
		return (NULL);
	}
	return (root);
}

static t_list	*ft_lex(char *str)
{
	t_list	*start;
	t_list	*tmp;
	int		size;
	int		i;

	size = get_size(str, 0);
	start = ft_lstnew(0, size - 1, str);
	if (!start)
		return (NULL);
	i = size;
	while (str[i])
	{
		size = get_size(str, i);
		tmp = ft_lstnew(i, size - 1, str);
		if (!tmp)
		{
			ft_lstclear(start);
			return (NULL);
		}
		ft_lstadd_back(&start, tmp);
		i = size;
	}
	return (lex_check(start));
	print_list(start, str);
}

int	is_something(t_list	*l_start)
{
	while (l_start && l_start->token == T_WHITE)
		l_start = l_start->next;
	if (!l_start)
		return (0);
	return (1);
}

int	ft_eval(char *str, t_map **env)
{
	t_list	*l_start;
	t_btree	*root;
	int		error;

	l_start = ft_lex(str);
	if (!l_start)
		return (free(str), 1);
	if (is_something(l_start) == 0)
		return (ft_lstclear(l_start), free(str), 0);
	l_start = ft_expand(l_start, str, env);
	l_start = ft_expand_join(&l_start);
	if (!l_start)
		return (1);
	root = ft_parse(l_start);
	if (!root)
		return (ft_lstclear(l_start), 2);
	if (!collapse_heredoc(root, env, root))
		error = collapse(root, env, root);
	else
		error = 1;
	free(str);
	btree_clear(root);
	return (error);
}

/*
echo123 | cat < test


Root value = ROOT
    Left value = LEFTRDIR
        Left value = PIPE
            Left value = COMMAND
                Left value = FUNCTION [echo]
                Right value = ARGS    [123]
            Right value = COMMAND
                Left value = FUNCTION [cat]
                Right value = ARGS    
        Right value = COMMAND
            Left value = FUNCTION [test]


Root value = ROOT
    Left value = PIPE
        Left value = COMMAND
            Left value = FUNCTION [echo]
            Right value = ARGS    [123]
		Right value = LEFTRDIR
			Left value = COMMAND
    	        Left value = FUNCTION [cat]
        	    Right value = ARGS    
        	Right value = COMMAND
        	    Left value = FUNCTION [test]



*/