/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:33:57 by haeem             #+#    #+#             */
/*   Updated: 2023/08/24 22:56:11 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSETREE_H
# define PARSETREE_H

# include "minishell.h"

typedef struct s_pstree
{
	t_token			token;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_pstree;

#endif