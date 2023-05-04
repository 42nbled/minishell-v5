/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:10:28 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/09 00:10:28 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*array;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	else if (start + len > slen)
		len = slen - start;
	array = malloc(len + 1);
	if (!array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = s[start + i];
		i++;
	}
	array[i] = '\0';
	return (array);
}
