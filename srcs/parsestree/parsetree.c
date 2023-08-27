/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/08/27 21:40:26 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"

void	init_pstree(t_pstree	**syntax)
{
	syntax = (t_pstree *)malloc(sizeof(t_pstree));
	(*syntax)->isroot = true;
}
