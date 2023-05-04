/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:32:30 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/23 19:32:30 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && --n && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}
