/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:20:02 by nbled             #+#    #+#             */
/*   Updated: 2023/02/23 08:20:04 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_list *start)
{
	t_list	*tmp;
	t_list	*ptr;

	ptr = start;
	while (ptr)
	{
		if (ptr->str)
			free(ptr->str);
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

/*
	export a="cho lel"

	[export][ ][a=]["][cho][ ][lel]["]
	
	e$a
	[e][$a]

	av
		echo
		lel
		NULL
	

	e"$a"

	av
		echo lel
		NULL
*/