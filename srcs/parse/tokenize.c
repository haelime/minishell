/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:07:07 by haeem             #+#    #+#             */
/*   Updated: 2023/09/25 19:27:35 by haeem            ###   ########seoul.kr  */
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
char	*make_token(char *input, char *a, char *b, t_list **out_tokens)
{
	t_token	*token;
	t_list	*temp;

	if (*b == '\0' || ft_isspace(*b))
		b--;
	token = (t_token *)malloc(sizeof(t_token));
	token->str = ft_substr(input, a - input, b - a + 1);
	token->type = get_type(token->str);
	temp = ft_lstnew(token);
	ft_lstadd_back(out_tokens, temp);
	return (b + 1);
}

// two pointer tokenizer, find | "" ''
void	tokenize(char *input, t_list **out_tokens)
{
	char	*start;
	char	*end;

	start = input;
	while (*start)
	{
		while (ft_isspace(*start))
			start++;
		end = start;
		while (*end != '\0' && !ft_strchr(" ><|&", *start))
		{
			if (ft_strchr("\'\"", *end) && *(end + 1) != '\0'
				&& isanotherquote(end))
				end = ft_strchr(end + 1, *end);
			if (istoken(*(end + 1)))
				break ;
			end++;
		}
		if (*start && *start == *(start + 1) && ft_strchr("><|", *start))
			++end;
		if (*start != '\0')
			start = make_token(input, start, end, out_tokens);
	}
}
