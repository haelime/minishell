/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:41:03 by haeem             #+#    #+#             */
/*   Updated: 2023/09/05 18:22:09 by haeem            ###   ########seoul.kr  */
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
	print_pstree(syntax->left);
	print_pstree(syntax->right);
}
