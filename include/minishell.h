/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cde-sede <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/03/06 17:16:38 by nbled			 #+#	#+#			 */
/*   Updated: 2023/05/08 17:57:04 by cde-sede         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/resource.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# include "defines.h"

// srcs/lexparse/check.c
int				is_last(t_list *tmp);
int				pipe_check(t_list *tmp);
void			put_error(t_list *tmp);
int				redir_check(t_list *tmp);
t_list			*lex_check(t_list *start);

// srcs/lexparse/lexer.c
void			get_token(t_list *start, char *str);

// srcs/lexparse/get_size.c
int				get_size(char *str, int i);

// srcs/lexparse/quote_check.c
int				quote_check(t_list *tmp);

// srcs/lexparse/state.c
t_list			*state_command_right(t_list *l_start, t_btree *ast_node);
t_list			*state_command(t_list *l_start, t_btree *ast_node);
t_list			*state_pipe(t_list *l_start, t_btree *ast_node);

// srcs/lexparse/state.c
t_base_result	state_base(t_list *l_start, t_btree *ast_node);

// srcs/lexparse/join_expand.c
void			ft_joindelete(t_list **l_start, t_token expected);

// srcs/lexparse/join_expand.c
void			ft_move(t_list **pile_a, t_list **l_start);

// srcs/lexparse/join_expand.c
t_list			*ft_moveredir(t_list *l_start);

// srcs/lexparse/join_expand.c
void			ft_joinjoin(t_list *l_start);
t_list			*ft_expand_join(t_list **l_start);

// srcs/lexparse/join_expand.c

// srcs/print.c
void			print_list(t_list *tmp, char *str);
void			print_lst_intree(t_list *node, char *str);
void			print_value(t_btree *root);
void			show_btree(t_btree *root, int depth, char *str);

// srcs/utils/ft_strcat.c
void			ft_strcat(char *dst, char const *src);

// srcs/utils/ft_strndup.c
char			*ft_strndup(const char *s1, int len);

// srcs/utils/signal_handler.c
void			handle_sigint(int sig);

// srcs/utils/ft_realloc.c
void			*ft_realloc(void *src, size_t old, size_t len);

// srcs/utils/ft_strnstr.c
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);

// srcs/utils/ft_strstr.c
char			*ft_strstr(char *str, char *to_find);

// srcs/utils/ft_isalpha.c
int				ft_isalpha(int c);

// srcs/utils/ft_isalnum.c
int				ft_isalnum(int c);

// srcs/utils/ft_strcmp.c
int				ft_strcmp(const char *s1, const char *s2);

// srcs/utils/ft_isdigit.c
int				ft_isdigit(int c);

// srcs/utils/ft_findi.c
int				ft_findi(char *str, char find);

// srcs/utils/ft_swapstr.c
void			ft_swap_str(char **a, char **b);

// srcs/utils/get_next_line.c
char			*get_next_line(int fd);

// srcs/utils/ft_strcpy.c
void			ft_strcpy(char *dst, const char *src);

// srcs/utils/ft_strncmp.c
int				ft_strncmp(const char *s1, const char *s2, size_t n);

// srcs/utils/ft_strlen.c
size_t			ft_strlen(const char *s);

// srcs/utils/ft_putstr_fd.c
void			ft_putstr_fd(char *s, int fd);

// srcs/utils/ft_substr.c
char			*ft_substr(char *s, unsigned int start, size_t len);

// srcs/utils/ft_strchr.c
char			*ft_strchr(const char *s, int c);

// srcs/utils/ft_atoi.c
int				ft_atoi(const char *nptr);

// srcs/utils/ft_itoa.c
char			*ft_itoa(int nb);

// srcs/utils/ft_strjoin.c
char			*ft_strjoin(char *s1, char *s2);

// srcs/utils/ft_split.c
char			**ft_split(char const *s, char c);

// srcs/utils/issomething.c
int				ft_isspace(int c);
int				ft_isasep(const char c);

// srcs/utils/ft_errors.c
char			*ft_jointhree(char *s1, char *s2, char *s3);
int				ft_error(char *msg, char *var, char *end, int r);

// srcs/utils/ft_strrchr.c
char			*ft_strrchr(const char *s, int c);

// srcs/utils/ft_strdup.c
char			*ft_strdup(const char *s1);

// srcs/utils/ft_splitexpand.c
char			**ft_splitexpand(char const *s);

// srcs/utils/ft_strlcpy.c
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

// srcs/main.c
int				last_ret(int i, int set);

// srcs/builtins/unset.c
int				f_unset(t_fargs *info);

// srcs/builtins/exit.c
int				f_exit(t_fargs *info);

// srcs/builtins/exec.c
int				f_exec(t_fargs *info);

// srcs/builtins/cd.c
int				f_cd(t_fargs *info);

// srcs/builtins/env.c
int				f_env(t_fargs *info);

// srcs/builtins/echo.c
int				f_echo(t_fargs *info);

// srcs/builtins/export.c
int				f_export(t_fargs *info);

// srcs/builtins/pwd.c
int				f_pwd(t_fargs *info);

// srcs/list/ft_lstclear.c
void			ft_lstclear(t_list *start);

// srcs/list/ft_lstadd_back.c
void			ft_lstadd_back(t_list **pile, t_list *n);

// srcs/list/ft_lstnew.c
t_list			*ft_lstnew(int start, int len, char *str);
t_list			*ft_lstnew_expand(char *str, t_token t);

// srcs/list/ft_lstlast.c
t_list			*ft_lstlast(t_list *lst);

// srcs/ft_expand.c
t_list			*ft_expand_env(t_list *l_start, char *str, t_map **env);
t_list			*ft_expand_env_dquote(t_list *l_start, char *str, t_map **env);
void			ft_expand_word(t_list *tmp, char *str);
t_list			*ft_expand(t_list *l_start, char *str, t_map **env);

// srcs/btree/btree_join.c
void			btree_join(t_btree **base, t_btree *root);

// srcs/btree/btree_delete.c
void			btree_clear(t_btree *root);

// srcs/btree/btree_new.c
t_btree			*btree_new(void *data, int token);

// srcs/prompt.c
char			*pwdcolor(int ret);
char			*get_prompt(int ret, t_map **env);

// srcs/ft_eval.c
t_btree			*ft_parse(t_list *l_start);
int				is_something(t_list *l_start);
int				ft_eval(char *str, t_map **env);

// srcs/collapse/heredoc_collapse.c
int				run_heredoc_inredir(t_btree *ast_node, t_map **env,
					t_btree *root_);
int				collapse_heredoc(t_btree *ast_node, t_map **env,
					t_btree *root_);

// srcs/collapse/heredoc_input.c
int				getwrite(int fd, char *delim);

// srcs/collapse/heredoc_utils.c
char			*heredoc_path(void);
t_fargs			**heredoc_static_pack(t_fargs **pack);
char			**heredoc_static_delim(char **delim);
char			**heredoc_static_file(char **file);

// srcs/collapse/rdir.c
int				run_rdir(t_btree *ast_node, t_map **env, t_btree *root_);
int				run_rdir_inredir(t_btree *ast_node, t_map **env,
					t_btree *root_);
int				run_rrdir(t_btree *ast_node, t_map **env, t_btree *root_);
int				run_rrdir_inredir(t_btree *ast_node, t_map **env,
					t_btree *root_);

// srcs/collapse/pipe.c
int				run_pipe(t_btree *ast_node, t_map **env, t_btree *root_);

// srcs/collapse/collapse.c
t_fargs			*pack(t_btree *ast_node, t_map **env, t_btree *root_);
void			free_pack(t_fargs *info);
void			free_ac(t_fargs *info);
int				run_command(t_btree *ast_node, t_map **env, t_btree *root_);
int				run_command_inpipe(t_btree *ast_node, t_map **env,
					t_btree *root_);
int				collapse(t_btree *root, t_map **env, t_btree *root_);

// srcs/collapse/redirections.c
int				run_redir(t_btree *ast_node, t_map **env, t_btree *root_,
					t_token *last);
int				run_redir_inredir(t_btree *ast_node, t_map **env,
					t_btree *root_);

// srcs/collapse/path.c
int				ft_find_cmd_path(char *cmd, char **path, char **result);
char			**exportpath(t_map *env);

// srcs/collapse/pipe_exec.c
int				f_exec_inpipe(t_fargs *info);

// srcs/collapse/ldir.c
int				run_ldir(t_btree *ast_node, t_map **env, t_btree *root_);
int				run_ldir_inredir(t_btree *ast_node, t_map **env,
					t_btree *root_);

// srcs/collapse/heredoc.c
void			heredoc_sigint(int sig);
int				open_heredoc(char *path, char *delim);
int				run_heredoc(t_btree *ast_node, t_map **env, t_btree *root_);
int				get_one_heredoc(char *file, char *delim, t_fargs *info);

// srcs/env/expand.c
int				extract_key(char *str);
char			*extract_value(char *s, t_map *env);

// srcs/env/defaults.c
char			**default_environ(void);
t_map			*envcopy(t_map *base);
void			sort_env(t_map *lst);

// srcs/env/str.c
char			**get_av(t_btree *node);

// srcs/env/shlvl.c
void			setshlvl(t_map **env);

// srcs/env/creation.c
t_map			*load_env(char **e);
t_map			*map_new(char *key, char *value);
int				env_delim(char *s);
int				env_split(char *s, char **key, char **value);
t_map			*map_fromstring(char *s);

// srcs/env/env.c
void			envfreeone(t_map *e);
void			free_map(t_map *e);

// srcs/env/env.c
char			**export(t_map *e);

// srcs/env/functions.c
int				set_env(char *key, char *value, t_map **env);
char			*get_env(char *key, t_map *env);
void			show_env(t_map *env);

t_fargs			**execpipe_static_pack(t_fargs **pack);
void			execpipe_exitfree(int signal);
void			execpipe_free_environ(char **environ);
void			execpipe_coredump(int signal);
#endif
