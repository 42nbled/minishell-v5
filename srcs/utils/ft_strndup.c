/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:53:22 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/23 11:53:22 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*array;

	if (len < 0)
		return (NULL);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	ft_strlcpy(array, s1, len + 1);
	return (array);
}
