/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astreelib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:33:57 by haeem             #+#    #+#             */
/*   Updated: 2023/08/05 20:42:00 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREELIB_H
# define ASTREELIB_H

typedef struct s_ast
{
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;
#endif