/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:33:57 by haeem             #+#    #+#             */
/*   Updated: 2023/09/15 19:11:07 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSETREE_H
# define PARSETREE_H

# include "minishell.h"
# include "../libft/include/libft.h"

typedef struct s_token	t_token;

typedef enum e_tree_node_type
{
	NODE_UNKNOWN = 0,
	NODE_COMMAND_BLOCK,
	NODE_PIPE
}	t_tree_node_type;

typedef struct s_tree	t_tree;
typedef struct s_tree
{
	void			*data;

	t_tree			*left;
	t_tree			*right;
}	t_tree;

t_tree	*make_pstree(t_list *chunks, t_hashmap *envmap);

#endif