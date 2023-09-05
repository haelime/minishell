/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:33:57 by haeem             #+#    #+#             */
/*   Updated: 2023/09/05 18:13:27 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSETREE_H
# define PARSETREE_H

# include "minishell.h"
# include "../libft/include/libft.h"

typedef struct s_token	t_token;

typedef struct s_tree
{
	void			*data;

	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

t_tree	*make_pstree(t_list *chunks, t_hashmap *envmap);

#endif