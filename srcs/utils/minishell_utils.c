/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:09 by haeem             #+#    #+#             */
/*   Updated: 2023/09/26 17:36:57 by hyunjunk         ###   ########.fr       */
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

__attribute__((noreturn))
void	msg_exit(const char *str, int err_code)
{
	printf("%s", str);
	exit(err_code);
}

__attribute__((noreturn))
void	str_msg_exit(const char *str, const char *str_arg, int err_code)
{
	printf(str, str_arg);
	exit(err_code);
}

int	str_msg_ret(const char *str, const char *str_arg, int err_code)
{
	printf(str, str_arg);
	return (err_code);
}
