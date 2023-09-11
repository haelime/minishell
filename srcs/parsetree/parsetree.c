/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/09/11 15:54:45 by haeem            ###   ########seoul.kr  */
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
	// const t_type	type = ((t_token *)(node->data))->type;
	(void)node;
	return (*root);
}

void	build_pstree(t_tree **syntax, t_list *chunks)
{
	t_tree	*node;
	t_token	*token;

	while (chunks)
	{
		node = make_node_pstree(chunks);
		token = (t_token *)chunks->content;
		rec_insert_pstree(syntax, node);
		chunks = chunks->next;
	}
}

// print_pstree(syntax);
t_tree	*make_pstree(t_list *chunks, t_hashmap *envmap)
{
	t_tree	*syntax;

	syntax = NULL;
	build_pstree(&syntax, chunks);
	rec_replace_dollar(syntax, envmap);
	// check_syntax(syntax);
	return (syntax);
}
