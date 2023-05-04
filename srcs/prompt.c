/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:52:46 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/22 13:52:46 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pwdcolor(int ret)
{
	if (ret == 0)
		return (GREEN_ARROW);
	return (RED_ARROW);
}

char	*get_prompt(int ret)
{
	char	*tmp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	tmp = ft_jointhree(pwdcolor(ret), ft_strrchr(cwd, '/') + 1, ": ");
	free(cwd);
	return (tmp);
}
