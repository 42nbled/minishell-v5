/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:46:50 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/23 11:46:50 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_key(char *str, int *join)
{
	int	i;

	i = 0;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (-1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
	{
		*join = 1;
		return (i + 1);
	}
	else if (str[i] == '=')
		return (i);
	else if (str[i] == '\0')
		return (0);
	return (-1);
}

static void	show_(t_map *env)
{
	while (env)
	{
		if (env->value)
			printf("export %s=\"%s\"\n", env->key, env->value);
		else if (env->key)
			printf("export %s=\"\"\n", env->key);
		env = env->next;
	}
}

static void	export_printenv(t_map **env)
{
	t_map	*tmp;

	tmp = envcopy(*env);
	sort_env(tmp);
	show_(tmp);
	free_map(tmp);
}

static void	export_addkey(char *av, int join, t_map **env)
{
	char	*key;
	char	*value;
	char	*tmp;

	if (join)
		key = ft_strndup(av, ft_findi(av, '+'));
	else
		key = ft_strndup(av, ft_findi(av, '='));
	if (ft_strchr(av, '='))
		value = ft_strdup(ft_strchr(av, '=') + 1);
	else
	{
		free(key);
		return ;
	}
	if (get_env(key, *env) && join == 1)
	{
		tmp = value;
		value = ft_strjoin(get_env(key, *env), value);
		free(tmp);
	}
	set_env(key, value, *env);
	free(key);
	free(value);
}

int	f_export(t_fargs *info)
{
	int	i;
	int	join;
	int	ret;

	i = 0;
	join = 0;
	ret = 0;
	if (info->ac == 1)
		export_printenv(info->env);
	while (++i < info->ac)
	{
		if (export_key(info->av[i], &join) >= 0)
			export_addkey(info->av[i], join, info->env);
		else
		{
			ft_error("export: `", info->av[i], "': not a valid identifier", 1);
			ret = 1;
		}
	}
	return (ret);
}
