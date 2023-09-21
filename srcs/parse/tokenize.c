/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:07:07 by haeem             #+#    #+#             */
/*   Updated: 2023/09/21 17:28:08 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

t_type	redirection(char *str)
{
	if (*str == '>' && *(str + 1) == '>')
		return (REDIRECT_APPEND);
	else if (*str == '<' && *(str + 1) == '<')
		return (REDIRECT_HEREDOC);
	else if (*str == '<')
		return (REDIRECT_IN);
	else if (*str == '>')
		return (REDIRECT_OUT);
	return (WORD);
}

t_type	get_type(char *str)
{
	if (ft_strchr("><", *str))
		return (redirection(str));
	else if (*str == '|')
		return (PIPE);
	else
		return (WORD);
	return (WORD);
}

// 	print_chunks(chunks);
char	*make_token(char *input, char *begin, char *end, t_list **out_tokens)
{
	t_token	*token;
	t_list	*temp;

	if (*end == '\0' || ft_isspace(*end))
		end--;
	token = (t_token *)malloc(sizeof(t_token));
	token->str = ft_substr(input, begin - input, end - begin + 1);
	token->type = get_type(token->str);
	temp = ft_lstnew(token);
	ft_lstadd_back(out_tokens, temp);
	return (end + 1);
}

// two pointer tokenizer, find | "" ''
void	tokenize(char *input, t_list **out_tokens)
{
	char	*begin;
	char	*end;

	begin = input;
	while (*begin)
	{
		while (ft_isspace(*begin))
			begin++;
		end = begin;
		while (*end != '\0' && !ft_strchr(" ><|&", *begin))
		{
			if (ft_strchr("\'\"", *end) && *(end + 1) != '\0'
				&& isanotherquote(end))
				end = ft_strchr(end + 1, *end);
			if (istoken(*(end + 1)))
				break ;
			end++;
		}
		if (*begin && *begin == *(begin + 1) && ft_strchr("><|", *begin))
			++end;
		if (*begin != '\0')
			begin = make_token(input, begin, end, out_tokens);
	}
}
