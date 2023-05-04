/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:31:07 by nbled             #+#    #+#             */
/*   Updated: 2023/03/13 07:31:08 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_of_word(char *str, int i)
{
	if (str[i] && str[i] == '$')
		i++;
	while (str[i] && !ft_isasep(str[i]) && !isspace(str[i]) && str[i] != '$')
	{
		if (str[i] && str[i + 1] && str[i] == 92)
			i += 2;
		else
			i++;
	}
	return (i);
}

int	get_size(char *str, int i)
{
	if (str[i] && str[i + 1] && str[i] == 92)
		i = size_of_word(str, i + 2);
	else if ((str[i] && str[i + 1])
		&& (((str[i] == '<') && (str[i + 1] == '<'))
			|| ((str[i] == '>') && (str[i + 1] == '>'))))
		i += 2;
	else if (str[i] && ft_isasep(str[i]))
		i++;
	else if (str[i] && isspace(str[i]))
		while (str[i] && isspace(str[i]))
				i++;
	else
		i = size_of_word(str, i);
	return (i);
}
