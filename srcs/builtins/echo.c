/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:09:21 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 19:18:55 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmpchr(char *str, char c)
{
	int	i;

	i = -1;
	if (!str || !*str)
		return (1);
	while (str[++i])
	{
		if (str[i] != c)
			return (1);
	}
	return (0);
}

static int	echo_(int ac, char **av, int i, int n)
{
	while (i < ac)
	{
		if (write(1, av[i], ft_strlen(av[i])) == -1)
			return (ft_error("write: ", strerror(errno), "", 1));
		if (i++ + 1 < ac)
			if (write(1, " ", 1) == -1)
				return (ft_error("write: ", strerror(errno), "", 1));
	}
	if (n)
		if (write(1, "\n", 1) == -1)
			return (ft_error("write: ", strerror(errno), "", 1));
	return (0);
}

int	f_echo(t_fargs *info)
{
	int	i;

	i = 1;
	if (info->ac == 1)
		printf("\n");
	if (info->ac > 1 && info->av[1][0] == '-'
			&& !ft_cmpchr(info->av[1] + 1, 'n'))
	{
		while (i < info->ac && ft_strlen(info->av[i]) > 1
			&& info->av[i][0] == '-'
					&& ft_cmpchr(info->av[i] + 1, 'n'))
			i++;
		return (echo_(info->ac, info->av, i + 1, 0));
	}
	else if (info->ac > 1)
		return (echo_(info->ac, info->av, i, 1));
	return (0);
}
