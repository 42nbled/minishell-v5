/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:19:28 by nbled             #+#    #+#             */
/*   Updated: 2023/05/04 16:14:33 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **pile, t_list *n)
{
	t_list	*ptr;

	if (!pile || !n)
		return ;
	if (!(*pile))
	{
		*pile = n;
		return ;
	}
	ptr = *pile;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = n;
}
