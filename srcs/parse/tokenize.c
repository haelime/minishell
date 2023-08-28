/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:07:07 by haeem             #+#    #+#             */
/*   Updated: 2023/08/28 20:35:50 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

bool	isanotherquote(char *begin)
{
	char	quote;

	quote = *begin;
	begin++;
	while (*begin)
	{
		if (*begin == quote)
			return (true);
		begin++;
	}
	return (false);
}

bool	isparenclosed(char *begin)
{
	const char	paren = ')';

	begin++;
	while (*begin)
	{
		if (*begin == paren)
			return (true);
		begin++;
	}
	return (false);
}

char	*tryfutherparen(char *begin)
{
	char	*ret;

	ret = begin;
	while (*begin)
	{
		if (*begin == ')')
			ret = begin;
		begin++;
	}
	return (ret);
}

// 	print_chunks(chunks);
char	*make_token(char *input, char *begin, char *end, t_list **chunks)
{
	char	*token;
	t_list	*temp;

	if (*end == '\0')
		end--;
	if (*begin == '(' && isparenclosed(begin))
		end = tryfutherparen(begin + 1);
	token = ft_substr(input, begin - input, end - begin + 1);
	temp = ft_lstnew(token);
	ft_lstadd_back(chunks, temp);
	return (end + 1);
}

// two pointer tokenizer, find | || && () "" ''
t_list	*tokenize(char *input, t_list **chunks)
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
			if (istoken(*(end + 1)) || (*(end + 1) == '&' && *(end + 2) == '&')
				|| ((*(end + 1) == '(') && isparenclosed(end + 1)))
				break ;
			end++;
		}
		if (*begin && *begin == *(begin + 1) && ft_strchr("><|&", *begin))
			++end;
		if (*begin != '\0')
			begin = make_token(input, begin, end, chunks);
	}
	return (*chunks);
}
