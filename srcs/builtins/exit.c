/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:42:49 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 18:48:17 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LONG_MAX 0x7fffffffffffffff
#define LONG_MIN 0x8000000000000000

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (ft_error("exit: ", str, ": numeric argument required", 1));
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (ft_error("exit: ", str, ": numeric argument required", 1));
	return (1);
}

static long	result_check(long result, int sign, int over, char *nptr)
{
	if ((result > LONG_MAX && sign == 1) || over == 1)
		return (ft_error("exit: ", nptr, ": numeric argument required", 2));
	if ((long unsigned)result > LONG_MIN && sign == -1)
		return (ft_error("exit: ", nptr, ": numeric argument required", 2));
	return (result * sign);
}

static long	ft_atoi2(const char *nptr)
{
	long	result;
	int		sign;
	size_t	i;
	int		over;
	long	tmp;

	i = 0;
	over = 0;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	sign = 1 + ((nptr[i] == '-' && ++i) * -2);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		tmp = result;
		result = result * 10 + (nptr[i++] - '0');
		if ((unsigned long)result == LONG_MIN && sign == -1)
			return (result_check(result, sign, 0, (char *)nptr));
		if (tmp > result)
			over = 1;
	}
	return (result_check(result, sign, over, (char *)nptr));
}

int	f_exit(t_fargs *info)
{
	long	status;

	ft_putstr_fd("exit\n", 2);
	if (info->ac > 2)
	{
		status = 2;
		if (!ft_isnum(info->av[1]) && ft_atoi2(info->av[1]) != 2
			&& (ft_atoi(info->av[1]) != 2))
			return (ft_error("exit: ", "", "too many arguments", 1));
		else if (ft_isnum(info->av[1]))
			status = ft_error("exit: ", info->av[1],
					": numeric argument required", 2);
	}
	else if (info->ac == 2 && ft_isnum(info->av[1]))
		status = 1;
	else if (info->ac == 2 && !ft_isnum(info->av[1]))
		status = ft_atoi2(info->av[1]);
	else
		status = 0;
	free_pack(info);
	exit(status);
	return (0);
}
