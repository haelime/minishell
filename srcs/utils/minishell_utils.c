/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:09 by haeem             #+#    #+#             */
/*   Updated: 2023/09/07 20:24:37 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

bool	isquoted(char *str, int i)
{
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	while (j < i)
	{
		if (str[j] == '\'')
			flag = !flag;
		j++;
	}
	if (flag == 1)
		return (true);
	return (false);
}

bool	isdoublequoted(char *str, int i)
{
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	while (j < i)
	{
		if (str[j] == '\"')
			flag = !flag;
		j++;
	}
	if (flag == 1)
		return (true);
	return (false);
}
