/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:24:17 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 17:33:04 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_path(void)
{
	static int	i = 1;
	char		*path;
	char		*nb;

	nb = ft_itoa(i);
	path = ft_jointhree("/tmp/", "minishell_tmp_", nb);
	i++;
	free(nb);
	return (path);
}


t_fargs	**heredoc_static_pack(t_fargs **pack)
{
	static t_fargs	**p = NULL;

	if (pack)
		p = pack;
	return (p);
}

char	**heredoc_static_delim(char **delim)
{
	static char	**d = NULL;

	if (delim)
		d = delim;
	return (d);
}

char	**heredoc_static_file(char **file)
{
	static char	**f = NULL;

	if (file)
		f = file;
	return (f);
}
