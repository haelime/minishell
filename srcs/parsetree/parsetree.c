/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/08/28 21:35:37 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"

// syntax = make_pstree(chunks);
t_pstree	*make_pstree(t_list *chunks, t_hashmap *envmap)
{
	t_pstree	*syntax;

	// init_pstree(&syntax);
	(void)envmap;
	(void)chunks;
	syntax = NULL;
	return (syntax);
}
