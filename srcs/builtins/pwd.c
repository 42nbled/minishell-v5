/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:01:48 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/22 15:01:48 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_pwd(t_fargs *info)
{
	char	*cwd;

	if (get_env("PWD", *(info->env)))
		printf("%s\n", get_env("PWD", *(info->env)));
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (ft_error("pwd: ", strerror(errno), "", 1));
		set_env("PWD", cwd, *(info->env));
		printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}
