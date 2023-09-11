/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:21:30 by haeem             #+#    #+#             */
/*   Updated: 2023/09/11 15:52:23 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"

bool	rec_check_syntax(t_tree *syntax)
{
	t_type	type;

	type = ((t_token *)(syntax->data))->type;
	if (syntax == NULL)
		return (true);
	if (type == PIPE || type == REDIRECT_APPEND || type == REDIRECT_OUT
		|| type == REDIRECT_IN || type == REDIRECT_HEREDOC)
		if (syntax->left == NULL)
			return (false);
	if (!rec_check_syntax(syntax->right) || !rec_check_syntax(syntax->left))
		return (false);
	return (true);
}
