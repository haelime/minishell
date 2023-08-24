/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:09 by haeem             #+#    #+#             */
/*   Updated: 2023/08/24 22:57:47 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

bool	has_quotes(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '\"')
			cmd = ft_strchr(cmd + 1, '\"');
		if (cmd == NULL)
			return (false);
		if (*cmd == '\'')
			cmd = ft_strchr(cmd + 1, '\'');
		if (cmd == NULL)
			return (false);
		++cmd;
	}
	return (true);
}
