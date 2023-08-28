/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:33:57 by haeem             #+#    #+#             */
/*   Updated: 2023/08/28 21:29:55 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSETREE_H
# define PARSETREE_H

# include "minishell.h"
# include "../libft/include/libft.h"

typedef struct s_token	t_token;

typedef struct s_pstree
{
	bool			isroot;
	t_token			*token;

	struct s_pstree	*left;
	struct s_pstree	*right;
}	t_pstree;

t_pstree	*make_pstree(t_list *chunks, t_hashmap *envmap);

#endif