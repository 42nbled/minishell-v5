/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:31:07 by nbled             #+#    #+#             */
/*   Updated: 2023/05/08 20:48:21 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_of_word(char *str, int i)
{
	if (str[i] && str[i] == '$')
		i++;
	while (str[i] && !ft_isasep(str[i]) && !isspace(str[i]) && str[i] != '$')
		i++;
	return (i);
}

int	get_size(char *str, int i)
{
	if ((str[i] && str[i + 1])
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
