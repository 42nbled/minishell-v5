/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:27:22 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/04 14:42:27 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *src, size_t old, size_t len)
{
	void	*new;

	new = malloc(len);
	if (!new)
	{
		free(src);
		return (NULL);
	}
	if (old < len)
		memcpy(new, src, old);
	else
		memcpy(new, src, len);
	free(src);
	return (new);
}
