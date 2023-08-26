/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:07:07 by haeem             #+#    #+#             */
/*   Updated: 2023/08/26 23:07:33 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"


void	give_type(t_list *chunks)
{
	while (chunks)
	{
		chunks->content = NULL;
		chunks = chunks->next;
	}
}

// two pointer tokenizer
t_list	*tokenize(char *input, t_list *chunks)
{
	char	*begin;
	char	*end;
	int		flag;

	begin = input;
	flag = 0;
	while (*begin)
	{
		while (ft_isspace(*begin))
			begin++;
		end = begin;
		flag    ^=      ft_isquote(*begin)
	}
	
	return (chunks);
}
