/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:48:50 by haeem             #+#    #+#             */
/*   Updated: 2023/09/22 21:30:57 by hyunjunk         ###   ########.fr       */
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

// input -> tokens -> cmd_blocks
t_list	*parse(char *input, t_hashmap *envmap)
{
	t_token	*token;
	t_list	*tokens;
	t_list	*p;

	tokens = NULL;
	tokenize(input, &tokens);
	p = tokens;
	while (p != NULL)
	{
		token = (t_token *)(p->content);
		if (ft_strchr(token->str, '$'))
			token->str = replace_dollar(token->str, envmap, 0);
		p = p->next;
	}
	if (check_parse_invalid(tokens))
	{
		printf("syntax error\n");
		free_tokens(&tokens);
		return (NULL);
	}
	print_chunks(tokens); // DEBUG
	return (tokens);
}
