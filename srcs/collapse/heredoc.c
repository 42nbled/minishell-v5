/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:47:11 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/26 20:08:26 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_delim(t_btree *node, char *str, t_map **env, t_btree *root_)
{
	t_fargs	*info;
	char	*file;
	t_list	*tmp;

	info = pack(node->right, str, env, root_);
	file = ft_strdup(info->av[0]);
	free_ac(info);
	free(info);
	if (!node->right->right)
		return (file);
	if (!node->left->right)
	{
		node->left->right = btree_new(node->right->right->data, T_ARGS);
		node->right->right->data = NULL;
		return (file);
	}
	tmp = (t_list *)node->left->right->data;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_list *)node->right->right->data;
	node->right->right->data = NULL;
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
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_error(HERE_DOC_WARNING, arg, arg2, -1);
	free(arg);
	free(arg2);
	return (*i = 0);
}

static int	check_len(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) - 1)
		return (0);
	return (1);
}

static int	getwrite(int fd, char *delim)
{
	char		*line;
	static int	i = 0;

	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	if (line && ft_strcmp(line, "\n"))
		i++;
	if (!line)
		return (null_line(&i, delim));
	else if (!ft_strncmp(delim, line, ft_strlen(delim))
		&& !check_len(delim, line))
		return (free(line), i = 0);
	else
		write(fd, line, ft_strlen(line));
	free(line);
	return (1);
}

int	open_heredoc(char *path, char *delim)
{
	int	fd;

	if (!delim)
		return (1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), "", 1));
	while (getwrite(fd, delim))
		;
	if (close(fd) == -1)
		return (ft_error("close: ", strerror(errno), "", 1));
	return (0);
}

static int	herepipe(char *file, t_fargs *info)
{
	int	fd;
	int	rcode;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), "", 1));
	dup2(fd, STDIN_FILENO);
	close(fd);
	rcode = collapse(info->ast_node, info->str, info->env, info->root_);
	free_ac(info);
	free(info);
	return (rcode);
}

int	run_heredoc(t_btree *ast_node, char *str, t_map **env, t_btree *root_)
{
	int		i;
	char	*file;
	char	*delim;
	int		rcode;

	i = fork();
	if (i == 0)
	{
		file = heredoc_path();
		delim = get_delim(ast_node, str, env, root_);
		rcode = 1;
		show_btree(root_, 0, str);
		if (!open_heredoc(file, delim))
			rcode = herepipe(file, pack(ast_node->left, str, env, root_));
		free(file);
		free(delim);
		free_map(*env);
		btree_clear(root_);
		free(str);
		exit(rcode);
	}	
	return (i);
}
