/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/09/07 16:39:12 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"

t_tree	*make_node_pstree(t_list *chunks)
{
	t_tree	*temp;

	temp = (t_tree *)malloc(sizeof(t_tree));
	temp->data = chunks->content;
	temp->left = NULL;
	temp->right = NULL;
	return (temp);
}

t_tree	*rec_insert_pstree(t_tree **root, t_tree *node)
{
	const t_type	type = ((t_token *)(node->data))->type;


	if (*root == NULL)
	{
		*root = node;
		return (*root);
	}
	if (type == PIPE)
		(*root)->right = rec_insert_pstree(&(*root)->right, node);
	else if (type == REDIRECT_APPEND || type == REDIRECT_OUT
		|| type == REDIRECT_IN || type == REDIRECT_HEREDOC)
		(*root)->right = rec_insert_pstree(&(*root)->right, node);
	else if (type == DOUBLE_PIPE || type == DOUBLE_AND)
		(*root)->right = rec_insert_pstree(&(*root)->right, node);
	else if (type == SUBSH)
		(*root)->right = rec_insert_pstree(&(*root)->right, node);
	else
		(*root)->left = rec_insert_pstree(&(*root)->left, node);
	return (*root);
}

void	build_pstree(t_tree **syntax, t_list *chunks)
{
	t_tree	*node;

	while (chunks)
	{
		node = make_node_pstree(chunks);
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
	(void)envmap;
	print_pstree(syntax);
	// check_syntax(syntax);
	return (syntax);
}
