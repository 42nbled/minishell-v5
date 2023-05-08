/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:47:11 by cde-sede          #+#    #+#             */
/*   Updated: 2023/05/08 07:21:32 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_delim(t_btree *node)
{
	char	*file;

	file = ft_strdup(((t_list*)node->left->data)->str);
	return (file);
}


static char	*heredoc_path(void)
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

static int	getwrite(int fd, char *delim)
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

static t_fargs	**pack__(t_fargs **pack)
{
	static t_fargs	**p = NULL;

	if (pack)
		p = pack;
	return (p);
}

static char	**delim__(char **delim)
{
	static char	**d = NULL;

	if (delim)
		d = delim;
	return (d);
}

static char	**file__(char **file)
{
	static char	**f = NULL;

	if (file)
		f = file;
	return (f);
}

void	heredoc_sigint(int sig)
{
	t_fargs	**pack;
	char	**file;
	char	**delim;

	(void)sig;
	pack = pack__(NULL);
	file = file__(NULL);
	delim = delim__(NULL);
	free_pack(*pack);
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
		file = ((t_list*)ast_node->data)->str;
		rcode = herepipe(file, ast_node->left, env, root_);
		free_map(*env);
		btree_clear(root_);
		exit(rcode);
	}	return (i);
}

int	run_heredoc_inredir(t_btree *ast_node, t_map **env, t_btree *root_)
{
	int		i;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		rcode = collapse(ast_node->left, env, root_);
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

	pack__(&info);
	file__(&file);
	delim__(&delim);
	pid = fork();
	if (pid == 0)
	{
		if (!open_heredoc(file, delim))
			status = 0;
		else
			status = 1;
		free(delim);
		free_pack(info);
		free(info);
		exit(status);
	}
	free(info);
	free(delim);
	if (waitpid(pid, &status, 0))
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	collapse_heredoc(t_btree *ast_node, t_map **env, t_btree *root_)
{
	static t_token	last = T_ROOT;
	char			*file;
	char			*delim;
	int				status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!ast_node || ast_node->token == T_COMMAND)
		return (0);
	if (ast_node->token == T_ROOT)
	{
		last = T_ROOT;
		return (collapse_heredoc(ast_node->left, env, root_));
	}
	if (ast_node->token == T_LEFTHRDC && last != T_LEFTHRDC)
	{
		printf("heredoc recursive\n");
		last = T_LEFTHRDC;
		status = collapse_heredoc(ast_node->left, env, root_);
		printf("heredoc done status=%d\n", status);
		if (status)
			return (status);
		file = heredoc_path();
		delim = get_delim(ast_node->right);
		ast_node->data = ft_lstnew_expand(file, T_ARGS);
		if (!get_one_heredoc(file, delim, pack(NULL, env, root_)))
			return (1);
		return (0);
	}
	if (ast_node->token == T_LEFTHRDC)
	{
		printf("heredoc inheredoc computed\n");
		last = T_LEFTHRDC;
		file = heredoc_path();
		delim = get_delim(ast_node->right);
		ast_node->data = ft_lstnew_expand(file, T_ARGS);
		return (collapse_heredoc(ast_node->left, env, root_));
	}
	else
	{
		last = ast_node->token;
		if (collapse_heredoc(ast_node->left, env, root_))
			return (1);
		if (collapse_heredoc(ast_node->right, env, root_))
			return (1);
	}
	return (0);
}
