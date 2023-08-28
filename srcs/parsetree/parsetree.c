/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/08/28 19:49:21 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"

// syntax = make_pstree(chunks);
t_pstree	*make_pstree(t_list *chunks)
{
	t_pstree	*syntax;

	syntax = (t_pstree *)malloc(sizeof(t_pstree));
	syntax->isroot = true;
	syntax->token = NULL;
	syntax->left = NULL;
	syntax->right = NULL;
	(void)chunks;
	return (syntax);
}
