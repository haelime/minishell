/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/08/30 18:33:35 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"

t_pstree	*make_node_pstree(t_list *chunks)
{
	t_pstree	*temp;

	temp = (t_pstree *)malloc(sizeof(t_pstree));
	temp->token = chunks->content;
	temp->left = NULL;
	temp->right = NULL;
}

void	insert_node_pstree(t_pstree *syntax, t_pstree *node)
{
	if (node->token->type == PIPE)
	{
		syntax->right = node;
	}
}

t_pstree	*build_pstree(t_pstree *syntax, t_list *chunks)
{
	t_pstree	*ret;
	t_pstree	*node;

	while (chunks)
	{
		node = make_node_pstree(chunks);
		insert_node_pstree(syntax, node);
		chunks = chunks->next;
	}
}

t_pstree	*make_pstree(t_list *chunks, t_hashmap *envmap)
{
	t_pstree	*syntax;

	build_pstree(syntax, chunks);
	rec_replace_dollar(syntax, envmap);
	check_syntax(syntax);
	return (syntax);
}
