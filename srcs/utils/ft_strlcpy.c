/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:23:33 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/07 02:26:55 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && size > 1)
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	if (size > 0)
		dst[i] = 0;
	while (src[i] != 0)
		i++;
	return (i);
}
