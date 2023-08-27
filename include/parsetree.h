/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:33:57 by haeem             #+#    #+#             */
/*   Updated: 2023/08/27 20:34:01 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSETREE_H
# define PARSETREE_H

# include "minishell.h"

typedef struct s_pstree
{
	bool			isroot;
	t_token			*token;

	struct s_pstree	*left;
	struct s_pstree	*right;
}	t_pstree;

void	init_pstree(t_pstree	**syntax);

#endif