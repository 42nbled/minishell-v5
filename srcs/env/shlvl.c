/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:23:59 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/22 15:23:59 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setshlvl(t_map *env)
{
	char	*lvl;
	char	*tmp;
	int		ilvl;

	lvl = get_env("SHLVL", env);
	if (!lvl)
		set_env("SHLVL", "0", env);
	lvl = get_env("SHLVL", env);
	ilvl = ft_atoi(lvl) + 1;
	if (ilvl > 999)
	{
		ft_error(SHLVL_WARNING, "", "", 0);
		ilvl = 1;
	}
	tmp = ft_itoa(ilvl);
	set_env("SHLVL", tmp, env);
	free(tmp);
}
