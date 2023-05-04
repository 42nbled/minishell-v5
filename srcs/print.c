#include "minishell.h"

void	print_list(t_list *tmp, char *str)
{
	int	size;
	int	i;

	while (tmp != NULL)
	{
		size = printf("i = "GREEN"%d"END, tmp->start);
		while (size++ < 18)
			printf(" ");
		size = printf(" | len = "YELLOW"%d"END, tmp->len);
		while (size++ < 22)
			printf(" ");
		size = printf(" | str = "MAGENTA"%s"END, tmp->str);
		while (size++ < 26)
			printf(" ");
		printf(" | token = "RED"%d"END, tmp->token);
		printf(" | str = \""BLUE);
		i = 0;
		while (i < tmp->len)
			printf("%c", str[tmp->start + i++]);
		printf(END"\" \n");
		tmp = tmp->next;
	}
}

static void	print_tabs(int numtab)
{
	int	i;

	i = 0;
	while (i < numtab)
	{
		printf("    ");
		i++;
	}
}

void	print_lst_intree(t_list *node, char *str)
{
	if (node->str)
		printf("[%s]", node->str);
	else if (node->start != -1)
		printf("[%.*s]", node->len, str + node->start);
	else
		printf("[]");
	if (!node->next)
		printf("\n");
	if (node->next)
		print_lst_intree(node->next, str);
}

void	print_value(t_btree *root)
{
	if (root->token == T_WORD)			 printf("value = "RED"WORD"END);
	else if (root->token == T_ENV)		 printf("value = "RED"ENV"END);
	else if (root->token == T_SQUOTE)	 printf("value = "RED"SQUOTE"END);
	else if (root->token == T_DQUOTE)	 printf("value = "RED"DQUOTE"END);
	else if (root->token == T_WHITE)	 printf("value = "RED"WHITE"END);
	else if (root->token == T_PIPE)		 printf("value = "RED"PIPE"END);
	else if (root->token == T_LEFTRDIR)	 printf("value = "RED"LEFTRDIR"END);
	else if (root->token == T_RIGHTRDIR) printf("value = "RED"RIGHTRDIR"END);
	else if (root->token == T_LEFTHRDC)	 printf("value = "RED"LEFTHRDC"END);
	else if (root->token == T_RAPPEND)	 printf("value = "RED"RIGHTHRDC"END);
	else if (root->token == T_LPAREN)	 printf("value = "RED"LPAREN"END);
	else if (root->token == T_RPAREN)	 printf("value = "RED"RPAREN"END);
	else if (root->token == T_ROOT)		 printf("value = "RED"ROOT"END);
	else if (root->token == T_COMMAND)	 printf("value = "RED"COMMAND"END);
	else if (root->token == T_ERROR)	 printf("value = "RED"ERROR"END);
	else if (root->token == T_FUNCTION)	 printf("value = "RED"FUNCTION "END);
	else if (root->token == T_ARGS)		 printf("value = "RED"ARGS    "END);
	else								 printf("value = "RED"?"END);
}

void	show_btree(t_btree *root, int depth, char *str)
{
	if (depth == 0)
		printf("Root ");
	print_value(root);
	//print_tabs(depth + 1);
	if (root->data)
		print_lst_intree((t_list*)root->data, str);
	else
		printf("\n");
	if (root->left)
	{
		print_tabs(depth + 1);
		printf(YELLOW"Left "END);
		show_btree(root->left, depth + 1, str);
	}
	if (root->right)
	{
		print_tabs(depth + 1);
		printf(GREEN"Right "END);
		show_btree(root->right, depth + 1, str);
	}
}
