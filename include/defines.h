/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:28:52 by cde-sede          #+#    #+#             */
/*   Updated: 2023/04/01 19:28:52 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define RED			"\x1b[31;1m"
# define GREEN			"\x1b[32;1m"
# define YELLOW			"\x1b[33;1m"
# define BLUE			"\x1b[34;1m"
# define MAGENTA		"\x1b[35;1m"
# define CYAN			"\x1b[36;1m"
# define GRAY			"\x1b[37;1m"
# define END			"\x1b[0m"
# define GREEN_ARROW	"\033[1m\033[32m❱ \033[0m"
# define RED_ARROW		"\033[1m\033[31m❱ \033[0m"

# define SHLVL_WARNING "warning: shell level (1000) too high, resetting to 1"
# define HERE_DOC_WARNING "warning: here-document at line "
# define HERE_DOC_EOF " delimited by end-of-file (wanted `"

// See https://www.in-ulm.de/~mascheck/various/argmax/
# ifndef _ARG_MAX
#  define _ARG_MAX 2097152
# endif
# ifndef _ARG_MAX_STRLEN
#  define _ARG_MAX_STRLEN 131072
# endif

typedef enum e_token
{
	T_WORD,
	T_ENV,
	T_SQUOTE,
	T_DQUOTE,
	T_WHITE,
	T_PIPE,
	T_LEFTRDIR,
	T_RIGHTRDIR,
	T_LEFTHRDC,
	T_RAPPEND,
	T_LPAREN,
	T_RPAREN,
	T_ROOT,
	T_COMMAND,
	T_FUNCTION,
	T_ARGS,
	T_PATH,
	T_ERROR,
	T_OK,
	S_PIPE,
}		t_token;

typedef struct s_list
{
	int				start;
	int				len;
	char			*str;
	t_token			token;
	struct s_list	*next;
}					t_list;

typedef struct s_btree
{
	t_token			token;
	void			*data;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

typedef struct s_map
{
	char			*key;
	char			*value;
	struct s_map	*next;
}					t_map;

typedef struct s_base_result
{
	t_token	status;
	t_list	*lst;
}			t_base_result;

typedef struct s_fargs
{
	int		ac;
	char	**av;
	t_btree	*ast_node;
	t_map	**env;
	t_btree	*root_;
}	t_fargs;

#endif
