/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:48:50 by haeem             #+#    #+#             */
/*   Updated: 2023/09/11 16:08:24 by haeem            ###   ########seoul.kr  */
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
		printf ("%s\n", ((t_token *)(chunks->content))->str);
		if (((t_token *)(chunks->content))->type == WORD)
			printf ("WORD\n");
		else if (((t_token *)(chunks->content))->type == PIPE)
			printf ("PIPE\n");
		else if (((t_token *)(chunks->content))->type == REDIRECT_IN)
			printf ("REDIRECT_IN\n");
		else if (((t_token *)(chunks->content))->type == REDIRECT_OUT)
			printf ("REDIRECT_OUT\n");
		else if (((t_token *)(chunks->content))->type == REDIRECT_APPEND)
			printf ("REDIRECT_APPEND\n");
		else if (((t_token *)(chunks->content))->type == REDIRECT_HEREDOC)
			printf ("REDIRECT_HEREDOC\n");
		else if (((t_token *)(chunks->content))->type
			== REDIRECT_HEREDOC_DELIMITER)
			printf ("REDIRECT_HEREDOC_DELIMITER\n");
		printf ("----------------\n");
		chunks = chunks->next;
	}
}

// tokenize → parsetree → excute
t_tree	*parse(char *input, t_hashmap *envmap)
{
	t_list	*chunks;
	t_tree	*syntax;

	chunks = NULL;
	chunks = tokenize(input, &chunks);
	syntax = make_pstree(chunks, envmap);
	print2d(syntax);
	// free_lst(chunks);
	// free (input);
	return (syntax);
}