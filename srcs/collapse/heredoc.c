/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:47:11 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 17:43:09 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint(int sig)
{
	t_fargs	**pack;
	char	**file;
	char	**delim;

	(void)sig;
	pack = heredoc_static_pack(NULL);
	file = heredoc_static_file(NULL);
	delim = heredoc_static_delim(NULL);
	free(*delim);
	free_pack(*pack);
	free(*pack);
	*pack = NULL;
	*file = NULL;
	*delim = NULL;
	exit(1);
}

int	open_heredoc(char *path, char *delim)
{
	int	fd;

	if (!delim)
		return (1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), "", 1));
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (getwrite(fd, delim))
		;
	if (close(fd) == -1)
		return (ft_error("close: ", strerror(errno), "", 1));
	return (0);
}

static int	herepipe(char *file, t_btree *ast_node, t_map **env, t_btree *root_)
{
	int	fd;
	int	rcode;

	fd = open(file, O_RDONLY, 0666);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), "", 1));
	dup2(fd, STDIN_FILENO);
	close(fd);
	rcode = collapse(ast_node, env, root_);
	return (rcode);
}

int	run_heredoc(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int		i;
	char	*file;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		file = ((t_list *)ast_node->data)->str;
		rcode = herepipe(file, ast_node->left, env, root_);
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}
	return (i);
}

int	get_one_heredoc(char *file, char *delim, t_fargs *info)
{
	int	pid;
	int	status;

	heredoc_static_pack(&info);
	heredoc_static_file(&file);
	heredoc_static_delim(&delim);
	pid = fork();
	if (pid == 0)
	{
		status = 1;
		if (open_heredoc(file, delim) == 0)
			status = 0;
		free(delim);
		free_pack(info);
		free(info);
		exit(status);
	}
	free(info);
	free(delim);
	if (!waitpid(pid, &status, 0))
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
