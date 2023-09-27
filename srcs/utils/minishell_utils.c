/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:09 by haeem             #+#    #+#             */
/*   Updated: 2023/09/27 21:31:17 by hyunjunk         ###   ########.fr       */
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
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s", str);
	exit(err_code);
}

__attribute__((noreturn))
void	str_msg_exit(const char *str, const char *str_arg, int err_code)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf(str, str_arg);
	exit(err_code);
}

int	str_msg_ret(const char *str, const char *str_arg, int err_code)
{
	const int	stdout_origin = dup(STDOUT_FILENO);

	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf(str, str_arg);
	dup2(stdout_origin, STDOUT_FILENO);
	return (err_code);
}
