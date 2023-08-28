/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:48:50 by haeem             #+#    #+#             */
/*   Updated: 2023/08/28 21:35:55 by haeem            ###   ########seoul.kr  */
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
		else if (((t_token *)(chunks->content))->type == REDIRECT_HEREDOC_DELIMITER)
			printf ("REDIRECT_HEREDOC_DELIMITER\n");
		else if (((t_token *)(chunks->content))->type == DOUBLE_PIPE)
			printf ("DOUBLE_PIPE\n");
		else if (((t_token *)(chunks->content))->type == DOUBLE_AND)
			printf ("DOUBLE_AND\n");
		else if (((t_token *)(chunks->content))->type == SUBSH)
			printf ("SUBSH\n");
		printf ("----------------\n");
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
	syntax = make_pstree(chunks, envmap);
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
