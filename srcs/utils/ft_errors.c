/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:29:09 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/22 13:29:09 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_jointhree(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*array;

	if (!s1 && !s2 && !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	array[0] = '\0';
	ft_strcpy(array, s1);
	ft_strcat(array, s2);
	ft_strcat(array, s3);
	return (array);
}

int	ft_error(char *msg, char *var, char *end, int r)
{
	char	*print;
	char	*tmp;

	tmp = ft_jointhree(msg, var, end);
	if (!tmp)
		return (1);
	print = ft_jointhree(GRAY"minishell: ", tmp, "\n"END);
	if (!print)
	{
		free(tmp);
		return (1);
	}
	ft_putstr_fd(print, 2);
	free(print);
	free(tmp);
	return (r);
}
