/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_invalid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:22:06 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/09/29 13:36:35 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_pipe_invalid(t_list *tokens)
{
	t_list	*p;

	if (((t_token *)tokens->content)->type == PIPE)
		return (1);
	if (((t_token *)ft_lstlast(tokens)->content)->type == PIPE)
		return (1);
	p = tokens;
	while (p != NULL)
	{
		if (p->next != NULL
			&& ((t_token *)p->content)->type == PIPE
			&& ((t_token *)p->next->content)->type == PIPE)
			return (1);
		p = p->next;
	}
	return (0);
}

static int	is_type_redirection(t_type type)
{
	if (type == REDIRECT_IN
		|| type == REDIRECT_OUT
		|| type == REDIRECT_APPEND
		|| type == REDIRECT_HEREDOC
		|| type == REDIRECT_HEREDOC_DELIMITER)
		return (1);
	return (0);
}

static int	check_redirection_invalid(t_list *tokens)
{
	t_list	*p;

	p = tokens;
	while (p != NULL)
	{
		if (is_type_redirection(((t_token *)p->content)->type))
		{
			if (p->next == NULL)
				return (1);
			else if (((t_token *)p->next->content)->type != WORD)
				return (1);
		}
		p = p->next;
	}
	return (0);
}

static	int	check_quote_closed(t_list *tokens)
{
	t_list	*p;
	char	*start;
	char	*end;

	p = tokens;
	while (p != NULL)
	{
		start = ((t_token *)(p->content))->str;
		end = start;
		while (*end)
		{
			if (ft_strchr("\'\"", *end))
			{
				if (*(end + 1) == '\0' || !isanotherquote(end))
					return (1);
				else
					end = ft_strchr(end + 1, *end);
			}
			end++;
		}
		p = p->next;
	}
	return (0);
}

/* @return	IF 		(is valid) 		THEN (0)
			ELSE 	(is invalid)	THEN (1)	*/
int	check_parse_invalid(t_list *tokens)
{
	if (check_quote_closed(tokens))
		return (1);
	if (check_pipe_invalid(tokens))
		return (1);
	if (check_redirection_invalid(tokens))
		return (1);
	return (0);
}
