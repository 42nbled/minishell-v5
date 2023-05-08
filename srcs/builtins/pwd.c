/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:01:48 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 01:24:13 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_pwd(t_fargs *info)
{
	char	*cwd;

	if (get_env("PWD", *(info->env)))
	{
		printf("ln21\n");
		printf("%s\n", get_env("PWD", *(info->env)));
	}
	else
	{
		printf("ln26\n");
		cwd = getcwd(NULL, 0);
		printf("ln28\n");
		if (!cwd)
		{
			printf("ln31\n");
			return (ft_error("pwd: ", strerror(errno), "", 1));
		}
		printf("ln34\n");
		printf("info=%p", (void*)info);
		printf("env=%p\n", (void*)*(info->env));
		set_env("PWD", cwd, (info->env));
		printf("ln35\n");
		free(cwd);
	}
	return (0);
}
