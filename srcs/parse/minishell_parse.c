/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:48:50 by haeem             #+#    #+#             */
/*   Updated: 2023/08/28 19:45:21 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

void	print_chunks(t_list *chunks)
{
	while (chunks)
	{
		printf ("%s\n", (char *)chunks->content);
		chunks = chunks->next;
	}
}

// tokenize → parsetree → excute
t_pstree	*parse(char *input, t_hashmap *envmap)
{
	t_list		*chunks;
	t_pstree	*syntax;

	chunks = NULL;
	chunks = tokenize(input, &chunks);
	print_chunks(chunks);
	(void)envmap;
	syntax = make_pstree(chunks);
	// 	free_lst(chunks);
	// 	return (syntax);
	// }
	// else
	// {
	// 	printf ("syntax error\n");
	// 	free (input);
	// 	return (NULL);
	return (NULL);
}
