/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:48:50 by haeem             #+#    #+#             */
/*   Updated: 2023/08/24 22:48:03 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

// tokenize → parsetree → excute
t_pstree	*parse(char *input, t_hashmap *envmap)
{
	t_lst		*chunks;
	t_pstree	*syntax;

	chunks = tokenize(input);
	init_pstree(syntax);
	if (check_grammar(chunks))
	{
		make_pstree(chunks, syntax);
		free_lst(chunks);
		return (syntax);
	}
	else
	{
		printf ("syntax error\n");
		free (input);
		return (NULL);
	}
}
