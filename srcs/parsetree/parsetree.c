/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/09/13 19:21:11 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"

extern void	exec_pipe(t_tree *syntax, t_hashmap *envmap);
extern void	exec_redirect(t_tree *syntax, t_hashmap *envmap);
extern void	exec_word(t_tree *syntax, t_hashmap *envmap);

t_tree	*make_node_pstree(t_list *chunks)
{
	t_tree	*temp;
	t_token	*token;

	temp = (t_tree *)malloc(sizeof(t_tree));
	token = (t_token *)chunks->content;
	temp->data = token;
	if (token->type == PIPE)
		token->exec = exec_pipe;
	else if (token->type == REDIRECT_APPEND || token->type == REDIRECT_OUT
		|| token->type == REDIRECT_IN || token->type == REDIRECT_HEREDOC)
		token->exec = exec_redirect;
	else if (token->type == WORD)
		token->exec = exec_word;
	temp->left = NULL;
	temp->right = NULL;
	return (temp);
}

// (*root)->left = rec_insert_pstree(&(*root)->left, node);
t_tree	*rec_insert_pstree(t_tree **root, t_tree *node)
{
	t_token	*token;

	token = (t_token *)node->data;

	if (token->type == PIPE)
		syntax_pipe(root, node);
	else if (token->type == REDIRECT_APPEND || token->type == REDIRECT_OUT
		|| token->type == REDIRECT_IN || token->type == REDIRECT_HEREDOC)
		syntax_redirect(root, node);
	else if (token->type == WORD)
		syntax_word(root, node);
	return (*root);
}

/*
@Return : returns the position of the chunk that should be read next. 
			It will be the position of PIPE or NULL.
*/
static t_list	*fill_subcontext_cmd_block(
	t_cmd_block *out_cmd_block, t_list *list_chunks)
{
	t_list		*now;
	t_token		*token;

	now = list_chunks;
	while (now != NULL)
	{
		token = (t_token *)now->content;
		if (token->type == PIPE)
			return (now);
		if (token->type == REDIRECT_IN)
			out_cmd_block->redirect_in = token->str;
		else if (token->type == REDIRECT_OUT)
			out_cmd_block->redirect_out = token->str;
		else if (token->type == REDIRECT_HEREDOC)
			out_cmd_block->redirect_heredoc = token->str;
		else if (token->type == REDIRECT_APPEND)
			out_cmd_block->redirect_append = token->str;
		now = now->next;
	}
	return (now);
}

/* It uses shallow copy about strings. 
	The caller should care about this. */
void	build_token_to_cmd_block(
	t_list **out_list_cmd_blocks, t_list *list_chunks)
{
	t_list		*now;
	t_token		*token;
	t_cmd_block	*new_block;

	now = list_chunks;
	while (now != NULL)
	{
		new_block = (t_cmd_block *)malloc(sizeof(t_cmd_block));
		ft_bzero(new_block, sizeof(t_cmd_block));
		// DEBUG
		if (((t_token *)now->content)->type != WORD)
			printf("DEBUG : token is not word. build_token_to_cmd_block()\n");
		new_block->cmd = (t_token *)now->content;
		fill_subcontext_cmd_block(new_block, now->next);
		now = now->next;
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
void	build_pstree(t_tree **syntax, t_list *chunks)
{
	t_tree	*node;
	t_token	*token;	
}

// print_pstree(syntax);
t_tree	*make_pstree(t_list *chunks, t_hashmap *envmap)
{
	t_list	*list_cmd_blocks;
	t_tree	*syntax;

	list_cmd_blocks = NULL;
	syntax = NULL;
	build_token_to_cmd_block(&list_cmd_blocks, chunks);
	build_pstree(&syntax, list_cmd_blocks);
	rec_replace_dollar(syntax, envmap);
	// check_syntax(syntax);
	return (syntax);
}
