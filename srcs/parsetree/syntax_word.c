/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:50:18 by haeem             #+#    #+#             */
/*   Updated: 2023/08/30 17:50:33 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"

void	rec_replace_dollar(t_pstree *syntax, t_hashmap *envmap)
{
	if (syntax->token->type == WORD)
	{
		syntax->token->str = replace_dollar(syntax->token->str, envmap);
	}
	if (syntax->left)
		rec_replace_dollar(syntax->left, envmap);
	if (syntax->right)
		rec_replace_dollar(syntax->right, envmap);
}