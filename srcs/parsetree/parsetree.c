/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/09/13 20:36:18 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"

extern void	exec_pipe(t_tree *syntax, t_hashmap *envmap);
extern void	exec_redirect(t_tree *syntax, t_hashmap *envmap);
extern void	exec_word(t_tree *syntax, t_hashmap *envmap);

// t_tree	*make_node_pstree(t_list *chunks)
// {
// 	t_tree	*temp;
// 	t_token	*token;

// 	temp = (t_tree *)malloc(sizeof(t_tree));
// 	token = (t_token *)chunks->content;
// 	temp->data = token;
// 	if (token->type == PIPE)
// 		token->exec = exec_pipe;
// 	else if (token->type == REDIRECT_APPEND || token->type == REDIRECT_OUT
// 		|| token->type == REDIRECT_IN || token->type == REDIRECT_HEREDOC)
// 		token->exec = exec_redirect;
// 	else if (token->type == WORD)
// 		token->exec = exec_word;
// 	temp->left = NULL;
// 	temp->right = NULL;
// 	return (temp);
// }

// (*root)->left = rec_insert_pstree(&(*root)->left, node);
// t_tree	*rec_insert_pstree(t_tree **root, t_tree *node)
// {
// 	t_token	*token;

// 	token = (t_token *)node->data;

// 	if (token->type == PIPE)
// 		syntax_pipe(root, node);
// 	else if (token->type == REDIRECT_APPEND || token->type == REDIRECT_OUT
// 		|| token->type == REDIRECT_IN || token->type == REDIRECT_HEREDOC)
// 		syntax_redirect(root, node);
// 	else if (token->type == WORD)
// 		syntax_word(root, node);
// 	return (*root);
// }

/*
@Return : returns the position of the chunk that should be read next. 
			It will be the position of PIPE or REDIRECT or NULL.
*/
static t_list	*fill_options_cmd_block(
	t_cmd_block *out_cmd_block, t_list *pos)
{
	t_list		*pos_origin;
	int			i;

	pos_origin = pos;
	out_cmd_block->num_options = 0;
	while (pos != NULL && ((t_token *)pos->content)->type == WORD)
	{
		out_cmd_block->num_options += 1;
		pos = pos->next;
	}
	out_cmd_block->options = (char **)malloc(
			(out_cmd_block->num_options + 1) * sizeof(char *));
	out_cmd_block->options[out_cmd_block->num_options] = NULL;
	pos = pos_origin;
	i = 0;
	while (pos != NULL && ((t_token *)pos->content)->type == WORD)
	{
		out_cmd_block->options[i++] = ((t_token *)pos->content)->str;
		pos = pos->next;
	}
	return (pos);
}

/*
@Return : returns the position of the chunk that should be read next. 
			It will be the position of PIPE or NULL.
*/
static t_list	*fill_subcontext_cmd_block(
	t_cmd_block *out_cmd_block, t_list *pos)
{
	t_token		*token;
	t_token		*next_token;

	while (pos != NULL && ((t_token *)pos->content)->type != PIPE)
	{
		token = (t_token *)pos->content;
		if (token->type == WORD)
			pos = fill_options_cmd_block(out_cmd_block, pos);
		else
		{
			next_token = (t_token *)pos->next->content;
			if (token->type == REDIRECT_IN)
				out_cmd_block->redirect_in = next_token->str;
			else if (token->type == REDIRECT_OUT)
				out_cmd_block->redirect_out = next_token->str;
			else if (token->type == REDIRECT_HEREDOC)
				out_cmd_block->redirect_heredoc = next_token->str;
			else if (token->type == REDIRECT_APPEND)
				out_cmd_block->redirect_append = next_token->str;
			pos = pos->next;
			pos = pos->next;
		}
	}
	return (pos);
}

/* It uses shallow copy about strings. 
	The caller should care about this. */
void	build_token_to_cmd_block(
	t_list **out_list_cmd_blocks, t_list *list_chunks)
{
	t_list		*now;
	t_cmd_block	*new_block;

	*out_list_cmd_blocks = NULL;
	now = list_chunks;
	while (now != NULL)
	{
		if (((t_token *)now->content)->type == PIPE)
			now = now->next;
		new_block = (t_cmd_block *)malloc(sizeof(t_cmd_block));
		ft_bzero(new_block, sizeof(t_cmd_block));
		// DEBUG
		if (((t_token *)now->content)->type != WORD)
			printf("DEBUG : token is not word. build_token_to_cmd_block() : %d\n", ((t_token *)now->content)->type);
		new_block->cmd = (t_token *)now->content;
		now = fill_subcontext_cmd_block(new_block, now->next);
		ft_lstadd_back(out_list_cmd_blocks, ft_lstnew(new_block));
	}
}

/*
          pipe
         /    \
       cmd  	pipe
	           /    \
			 cmd    NULL
			/
	   simple cmd

            cmd					    cmd
         /       \                /      \
    redirect	 simple_cmd   simple_cmd  NULL

        redirect
       /  	    \
   <,>,<<,>>	WORD(file name)

		simple cmd
		/		\
	WORD(exec)	simple cmd
				/	\
			WORD	WORD
*/
// void	build_pstree(t_tree **syntax, t_list *chunks)
// {
// 	t_tree	*node;
// 	t_token	*token;	
// }

// print_pstree(syntax);
t_tree	*make_pstree(t_list *chunks, t_hashmap *envmap)
{
	t_list	*list_cmd_blocks;
	t_tree	*syntax;

	list_cmd_blocks = NULL;
	syntax = NULL;
	build_token_to_cmd_block(&list_cmd_blocks, chunks);
	// DEBUG 
	t_list *p = list_cmd_blocks;
	for (; p != NULL; p = p->next)
	{
		t_cmd_block* now = (t_cmd_block *)p->content;
		printf("type = %d\n", now->type);
		printf("cmd.type = %d\n", now->cmd->type);
		printf("cmd.str = %s\n", now->cmd->str);
		printf("num_options = %d\n", now->num_options);
		for (int i = 0; i < now->num_options; i++)
		{
			printf("    %s\n", now->options[i]);
		}
		printf("redirect = %p %p %p %p\n", 
			now->redirect_in, now->redirect_out, now->redirect_append, now->redirect_heredoc);
		printf("\n\n");
	}

	(void)envmap;
	
	//build_pstree(&syntax, list_cmd_blocks);
	//rec_replace_dollar(syntax, envmap);
	// check_syntax(syntax);
	return (syntax);
}
