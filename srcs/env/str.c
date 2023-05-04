/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:59:01 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 21:32:26 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	getargs
		create buf
			if token is space skip
			for each token
				if token is word; join last buf with word
				if token is squote;
					for every token inside squotes
						cat token
					join last buf with string inside squotes
				if token is dquote;
					for every token inside dquotes
						if token is env
							replace env
							split replace result at every spaces
							and add each result to the global buf
							joining the first
				if token is space
					go to next buf making it NULL
*/

static char	*squotes(t_list **lst, char *str)
{
	t_list	*tmp;
	t_list	*start;
	int		n;
	char	*ret;

	start = *lst;
	tmp = start->next;
	n = tmp->start;
	while (tmp->token != start->token)
	{
		n += tmp->len;
		tmp = tmp->next;
	}
	*lst = tmp;
	ret = ft_substr(str, start->next->start, n);
	if (ft_strlen(ret))
		return (ret);
	free(ret);
	return (NULL);
}

static void	*joinav(char **name, char **av, int size)
{
	char	**new;

	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	new[0] = name[0];
	memcpy(new + 1, av, size * sizeof(char *));
	new[size + 1] = NULL;
	return (new);
}

char	**get_av(t_btree *node, char *str, t_map *env)
{
	char	**name;
	char	**args;
	char	**final;
	int		i;
	t_list	*temp;

	temp = (t_list *)node->left->data;
	name = token_getargs(temp, str, env);
	if (!name)
		return (NULL);
	if (!node->right)
		return (name);
	temp = (t_list *)node->right->data;
	args = token_getargs(temp, str, env);
	i = 0;
	while (args && args[i])
		i++;
	final = joinav(name, args, i);
	free(name);
	free(args);
	return (final);
}

void	case_tword(t_list *t, char *str, char ***buffer, int i)
{
	char	*val;
	char	*old;

	if (!buffer || !*buffer)
		return ;
	*buffer = ft_realloc(*buffer, sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2));
	old = (*buffer)[i];
	val = ft_substr(str, t->start, t->len);
	if (ft_strlen(val))
		(*buffer)[i] = ft_strjoin(old, val);
	free(old);
	free(val);
}

void	case_tsquote(t_list **t, char *str, char ***buffer, int i)
{
	char	*val;
	char	*old;

	*buffer = ft_realloc(*buffer, sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2));
	old = *buffer[i];
	val = squotes(t, str);
	*buffer[i] = ft_strjoin(*buffer[i], val);
	free(val);
	free(old);
}

char	*tenv_getval(t_list **t, char *str, t_map *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_substr(str, (*t)->start, (*t)->len);
	if (!tmp)
		return (NULL);
	if (ft_strcmp(tmp, "$") == 0)
	{
		free(tmp);
		return (ft_strdup("$"));
	}
	result = extract_value(tmp, env);
	free(tmp);
	if (!result)
		return (NULL);
	if (ft_strlen(result))
		return (result);
	free(result);
	return (NULL);
}

void	case_tenv(t_list **t, char *str, char ***buffer, int *i, t_map *env)
{
	char	*tmp;
	char	**tmp2;
	char	*old;
	int		j;
	int		k;

	tmp = tenv_getval(t, str, env);
	if (!tmp)
		return ;
	old = *buffer[*i];
	tmp2 = ft_split(tmp, ' ');
	free(tmp);
	(*buffer)[*i] = ft_strjoin(old, tmp2[0]);
	free(old);
	j = 0;
	while (tmp2[++j])
		;
	*buffer = ft_realloc(*buffer, sizeof(char *) * (*i + 1),
			sizeof(char *) * (*i + j + 2));
	free(tmp2[0]);
	k = j;
	while (--j > 0)
		(*buffer)[*i + j] = tmp2[j];
	*i = *i + k - 1;
	free(tmp2);
}

void	case_sqtenv(t_list **t, char *str, char ***buffer, int *i, t_map *env)
{
	char	*val;
	char	*old;

	if (!buffer || !*buffer)
		return ;
	val = tenv_getval(t, str, env);
	if (!val)
		return ;
	*buffer = ft_realloc(*buffer, sizeof(char *) * (*i + 1),
			sizeof(char *) * (*i + 2));
	old = (*buffer)[*i];
	if (ft_strlen(val))
		(*buffer)[*i] = ft_strjoin(old, val);
	free(old);
	free(val);
}

void	case_tdquote(t_list **t, char *str, char ***buffer, int *i, t_map *env)
{
	*t = (*t)->next;
	while (*t && (*t)->token != T_DQUOTE)
	{
		if ((*t)->token == T_ENV)
			case_sqtenv(t, str, buffer, i, env);
		else
			case_tword(*t, str, buffer, *i);
		*t = (*t)->next;
	}
}

static char	**returnvoid(char **buffer, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(buffer[j]);
	free(buffer);
	return (NULL);
}

void	skip_spaces(t_list **t, char **buffer, int *i)
{
	if (*buffer[*i])
		(*i)++;
	buffer[*i] = NULL;
	while (*t && (*t)->token == T_WHITE && (*t)->next->token == T_WHITE)
		*t = (*t)->next;
}

char	**token_getargs(t_list *tokens, char *str, t_map *env)
{
	char	**buffer;
	int		i;

	buffer = malloc(sizeof(char *) * 2);
	buffer[0] = ft_strdup("");
	i = 0;
	if (tokens->token == T_WHITE)
		tokens = tokens->next;
	while (tokens)
	{
		if (tokens->token == T_WORD)
			case_tword(tokens, str, &buffer, i);
		else if (tokens->token == T_SQUOTE)
			case_tsquote(&tokens, str, &buffer, i);
		else if (tokens->token == T_ENV)
			case_tenv(&tokens, str, &buffer, &i, env);
		else if (tokens->token == T_DQUOTE)
			case_tdquote(&tokens, str, &buffer, &i, env);
		else if (tokens->token == T_WHITE && tokens->next)
			skip_spaces(&tokens, buffer, &i);
		else if (ft_strlen(buffer[i]) == 0)
			return (returnvoid(buffer, i));
		tokens = tokens->next;
	}
	buffer[++i] = NULL;
	return (buffer);
}
