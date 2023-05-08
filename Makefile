NAME = minishell
INCLUDE = include/
SRC_DIR = srcs/
OBJ_DIR = obj/
CC = cc
CFLAGS = -Wall -Werror -Wextra -I./include -g -fsanitize=address -fsanitize=undefined -fsanitize=leak
RM = rm -f

SRC_MAIN = main
SRC_LEXPARSE = lexer join_expand check quote_check get_size state
SRC_COLLAPSE = collapse redirections pipe rdir ldir path heredoc pipe_exec
SRC_ENV = creation defaults env str functions shlvl expand
SRC_BUILTINS = exec echo cd pwd env exit unset export
SRC_UTILS = get_next_line ft_swapstr ft_atoi ft_strcmp ft_strncmp ft_itoa ft_isdigit ft_isalpha ft_isalnum ft_errors ft_putstr_fd ft_realloc ft_split ft_splitexpand ft_strcat ft_strdup ft_strndup ft_findi ft_strchr ft_strrchr ft_strcpy ft_strjoin ft_strlcpy ft_strlen ft_strnstr ft_strstr ft_substr issomething signal_handler
SRC_LIST = ft_lstadd_back ft_lstclear ft_lstnew ft_lstlast
SRC_BTREE = btree_join btree_delete btree_new
SRC_PRINT = print prompt ft_expand ft_eval

SRC_FILES += $(SRC_MAIN)
SRC_FILES += $(addprefix lexparse/, $(SRC_LEXPARSE))
SRC_FILES += $(addprefix collapse/, $(SRC_COLLAPSE))
SRC_FILES += $(addprefix env/, $(SRC_ENV))
SRC_FILES += $(addprefix builtins/, $(SRC_BUILTINS))
SRC_FILES += $(addprefix utils/, $(SRC_UTILS))
SRC_FILES += $(addprefix list/, $(SRC_LIST))
SRC_FILES += $(addprefix btree/, $(SRC_BTREE))
SRC_FILES += $(SRC_PRINT)

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

NUM_FILES = $(words $(SRC_FILES))
CURRENT_FILE = 1

define show_progress
	@echo -n "\033[0;34m [$(CURRENT_FILE)/$(NUM_FILES)] \033[0m"
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
endef

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)  -lreadline
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)lexparse
	@mkdir -p $(OBJ_DIR)collapse
	@mkdir -p $(OBJ_DIR)env
	@mkdir -p $(OBJ_DIR)builtins
	@mkdir -p $(OBJ_DIR)utils
	@mkdir -p $(OBJ_DIR)list
	@mkdir -p $(OBJ_DIR)btree
	@echo -n "\t"
	@echo "\033[0;32m [OK] \033[0m" $<
	$(show_progress)
	@($(CC) $(CFLAGS) -c $< -o $@ && echo "\033[0;32m [OK] \033[0m" $<) || (echo "\033[0;31m [ERROR] \033[0m" $< && exit 1)
clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
