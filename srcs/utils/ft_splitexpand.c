/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitexpand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:37:28 by nbled             #+#    #+#             */
/*   Updated: 2023/04/28 01:55:11 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(const char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] && !ft_isspace(s[i]))
			j++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (j);
}

static int	ft_str_len(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i + j] && !ft_isspace(s[i + j]))
		j++;
	return (j);
}

char	**ft_splitexpand(char const *s)
{
	char	**tab;
	int		size;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	size = ft_count_words(s);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (i < ft_count_words(s))
	{
		tab[i] = malloc(ft_str_len(s + j) + 1);
		k = 0;
		while (s[j] && ft_isspace(s[j]))
			j++;
		while (s[j] && !ft_isspace(s[j]))
			tab[i][k++] = s[j++];
		tab[i][k] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
