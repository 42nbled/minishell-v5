/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:21:20 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 17:33:04 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	null_line(int *i, char *delim)
{
	char	*arg;
	char	*arg2;

	arg = ft_itoa(*i);
	arg2 = ft_jointhree(HERE_DOC_EOF, delim, "\')");
	ft_error(HERE_DOC_WARNING, arg, arg2, -1);
	free(arg);
	free(arg2);
	return (*i = 1);
}

int	getwrite(int fd, char *delim)
{
	char		*line;
	static int	i = 0;

	line = readline("> ");
	if (line && ft_strcmp(line, "\n"))
		i++;
	if (!line)
		return (null_line(&i, delim));
	else if (!ft_strncmp(delim, line, ft_strlen(delim)))
	{
		i = 0;
		free(line);
		return (0);
	}
	else
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	return (free(line), 1);
}
