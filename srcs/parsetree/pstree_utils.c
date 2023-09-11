/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:41:03 by haeem             #+#    #+#             */
/*   Updated: 2023/09/11 16:02:25 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"

void	print_pstree(t_tree *syntax)
{
	if (syntax == NULL)
		return ;
	printf("%s\n", ((t_token *)(syntax->data))->str);
	printf ("type : %d\n", ((t_token *)(syntax->data))->type);
	print_pstree(syntax->left);
	print_pstree(syntax->right);
}

void	print2dutil(t_tree *root, int space)
{
	const int	count = 10;
	int			i;
	t_token		*token;

	if (root == NULL || root->data == NULL)
		return ;
	token = (t_token *)root->data;
	space += count;
	if (root->right)
		print2dutil(root->right, space);
	printf("\n");
	i = count;
	while (i < space)
	{
		printf(" ");
		i++;
	}
	printf("%s\n", token->str);
	if (root->left)
		print2dutil(root->left, space);
}

// Wrapper over print2DUtil()
void	print2d(t_tree *root)
{
	print2dutil(root, 0);
}
