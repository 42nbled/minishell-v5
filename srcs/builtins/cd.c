/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:21:10 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/22 13:21:10 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(char *av)
{
	char	*error;

	error = ft_strjoin(av, ": ");
	if (!error)
		return (1);
	ft_error("cd: ", error, strerror(errno), 1);
	free(error);
	return (1);
}

static void	replace_pwd(char *key, t_map **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	set_env(key, cwd, *env);
	free(cwd);
}

static int	fromhome(t_map **env)
{
	char	*home;

	home = NULL;
	home = get_env("HOME", *env);
	replace_pwd("OLDPWD", env);
	if (home && chdir(home))
		return (ft_error("cd: HOME not set", "", "", 1));
	else
		set_env("PWD", home, *env);
	return (0);
}

int	f_cd(t_fargs *info)
{
	int		i;

	i = 0;
	if (info->ac == 1)
		i = fromhome(info->env);
	else if (info->ac == 2)
	{
		replace_pwd("OLDPWD", info->env);
		if (!chdir(info->av[1]))
			replace_pwd("PWD", info->env);
		else
			i = cd_error(info->av[1]);
	}
	else
		i = ft_error("cd: too many arguments", "", "", 1);
	return (i);
}
