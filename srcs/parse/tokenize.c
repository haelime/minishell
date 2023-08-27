/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:07:07 by haeem             #+#    #+#             */
/*   Updated: 2023/08/27 23:08:46 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

// 	print_chunks(chunks);
char	*make_token(char *input, char *begin, char *end, t_list **chunks)
{
	char	*token;
	t_list	*temp;

	if (*end == '\0')
		end--;
	token = ft_substr(input, begin - input, end - begin + 1);
	temp = ft_lstnew(token);
	ft_lstadd_back(chunks, temp);
	return (end + 1);
}

bool	istoken(char ch)
{
	return (ch == '<' || ch == '>' || ch == '|');
}

void	flaghandler(char *begin, int *flag)
{
	if (*begin == '\'')
	{
		*flag ^= QUOTE;
		printf("flag changed to %d", *flag);
	}
	if (*begin == '\"')
	{
		*flag ^= DOUBLEQUOTE;
		printf("flag changed to %d", *flag);
	}
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
			if (ft_strchr("\'\"", *end) && *(end + 1) != '\0')
				end = ft_strchr(end + 1, *end);
			if (istoken(*(end + 1)) || *(end + 1) == ' '
				|| (*(end + 1) == '&' && *(end + 2) == '&'))
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
