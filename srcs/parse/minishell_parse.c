/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:48:50 by haeem             #+#    #+#             */
/*   Updated: 2023/09/28 18:14:24 by hyunjunk         ###   ########.fr       */
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

// a"'bc'"d"e" should be a'bc'd e
char	*get_removed_quotes(char *str)
{
	char	*start;
	char	*end;
	char	*ret;
	char	*cut;

	ret = ft_strdup("");
	start = str;
	end = start;
	while (*end)
	{
		if (ft_strchr("\'\"", *end) && *(end + 1) && isanotherquote(end))
		{
			cut = ft_substr(str, start - str, end - start);
			ret = ft_strjoinfree(&ret, &cut);
			start = end;
			end = ft_strchr(end + 1, *end);
			cut = ft_substr(str, start - str + 1, end - start - 1);
			ret = ft_strjoinfree(&ret, &cut);
			start = ++end;
		}
		end++;
	}
	ret = join_remain(&ret, &str, &start, &end);
	return (ret);
}

// a"'bc'"d"e" should be a'bc'de
void	rm_quotes(t_list **out_tokens)
{
	t_list	*p;
	char	*str;
	char	*ret;

	p = *out_tokens;
	ret = NULL;
	while (p != NULL)
	{
		str = ((t_token *)(p->content))->str;
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		{
			ret = get_removed_quotes(str);
			free(((t_token *)(p->content))->str);
			((t_token *)(p->content))->str = ret;
		}
		p = p->next;
	}
}

// input -> tokens -> cmd_blocks
t_list	*parse(char *input, t_hashmap *envmap)
{
	t_token	*token;
	t_list	*tokens;
	t_list	*p;
	char	*tmp;

	tokens = NULL;
	tokenize(input, &tokens);
	p = tokens;
	while (p != NULL)
	{
		token = (t_token *)(p->content);
		if (ft_strchr(token->str, '$'))
		{
			tmp = replace_dollar(token->str, envmap);
			free(token->str);
			token->str = tmp;
		}
		p = p->next;
	}
	if (check_parse_invalid(tokens))
	{
		printf("syntax error\n");
		free_tokens(&tokens);
		return (NULL);
	}
	rm_quotes(&tokens);
	//print_chunks(tokens); // DEBUG
	return (tokens);
}
