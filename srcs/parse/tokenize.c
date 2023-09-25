/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:07:07 by haeem             #+#    #+#             */
/*   Updated: 2023/09/25 19:10:55 by haeem            ###   ########seoul.kr  */
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
	char	*wd[2];

	wd[0] = input;
	while (*wd[0])
	{
		while (ft_isspace(*wd[0]))
			wd[0]++;
		wd[1] = wd[0];
		while (*wd[1] != '\0' && !ft_strchr(" ><|&", *wd[0]))
		{
			if (ft_strchr("\'\"", *wd[1]) && *(wd[1] + 1) != '\0'
				&& isanotherquote(wd[1]))
				wd[1] = ft_strchr(wd[1] + 1, *wd[1]);
			if (istoken(*(wd[1] + 1)))
				break ;
			wd[1]++;
		}
		if (*wd[0] && *wd[0] == *(wd[0] + 1) && ft_strchr("><|", *wd[0]))
			++wd[1];
		if (*wd[0] != '\0')
			wd[0] = make_token(input, wd[0], wd[1], out_tokens);
	}
}
