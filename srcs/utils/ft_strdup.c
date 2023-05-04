/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:39:56 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/22 15:39:56 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*array;
	size_t	i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	array = malloc(sizeof(char) * (i + 1));
	if (!array)
		return (NULL);
	ft_strlcpy(array, s1, i + 1);
	return (array);
}
