/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:16:29 by nbled             #+#    #+#             */
/*   Updated: 2023/05/07 01:26:49 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	routine(t_map **env)
{
	char			*str;
	char			*prompt;
	struct termios	p;

	tcgetattr(STDOUT_FILENO, &p);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt(last_ret(0, 0));
		str = readline(prompt);
		free(prompt);
		if (!str)
		{
			printf(RED"exit\n"END);
			break ;
		}
		if (*str)
			add_history(str);
		last_ret(ft_eval(str, env), 1);
		tcsetattr(STDIN_FILENO, TCSANOW, &p);
	}
	free_map(*env);
	return (last_ret(0, 0));
}

int	last_ret(int i, int set)
{
	static int	n = 0;

	if (set)
		n = i;
	return (n);
}

int	main(int ac, char **av, char **env)
{
	t_map	*e;
	char	**tenv;

	(void) av;
	if (ac > 1)
		return (0);
	if (!env || !*env)
	{
		tenv = default_environ();
		e = load_env(tenv);
		free(tenv[0]);
		free(tenv[1]);
		free(tenv[2]);
		free(tenv);
	}
	else
		e = load_env(env);
	setshlvl(e);
	last_ret(0, 1);
	return (routine(&e));
}
