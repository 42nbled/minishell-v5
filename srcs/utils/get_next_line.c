/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:09:27 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/23 19:09:27 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFFER_SIZE 1

static void	read_line(char **s, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		tmp = *s;
		*s = ft_strjoin(*s, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
}

static char	*get_line(char **s)
{
	char		*tmp;
	char		*line;
	int			i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	if ((*s)[i] == '\n')
		i++;
	line = ft_substr(*s, 0, i);
	tmp = *s;
	*s = ft_substr(tmp, i, ft_strlen(tmp) - i);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s[1024];

	if (fd < 0 || read(fd, NULL, 0) < 0 || fd > 1024)
		return (NULL);
	if (!ft_strchr(s[fd], '\n'))
		read_line(s + fd, fd);
	if (!s[fd])
		return (NULL);
	if (!s[fd][0])
	{
		free(s[fd]);
		s[fd] = NULL;
		return (NULL);
	}
	return (get_line(s + fd));
}
