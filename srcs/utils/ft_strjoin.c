/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:10:00 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/09 00:10:00 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*array;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	array[0] = '\0';
	ft_strcpy(array, s1);
	ft_strcat(array, s2);
	return (array);
}
