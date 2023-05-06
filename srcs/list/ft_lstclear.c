/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:20:02 by nbled             #+#    #+#             */
/*   Updated: 2023/05/06 23:48:51 by cde-sede         ###   ########.fr       */
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