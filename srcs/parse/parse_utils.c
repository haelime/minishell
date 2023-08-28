/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:25:03 by haeem             #+#    #+#             */
/*   Updated: 2023/08/28 21:08:29 by haeem            ###   ########seoul.kr  */
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

bool	istoken(char ch)
{
	return (ch == '<' || ch == '>' || ch == '|'
		|| ch == ' ');
}
