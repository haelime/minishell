/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:03:36 by haeem             #+#    #+#             */
/*   Updated: 2023/09/26 16:45:29 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"

void	dup_stdio(int in_fd, int out_fd)
{
	dup2(in_fd, STDIN);
	dup2(out_fd, STDOUT);
}

bool	is_builtin(t_cmd_block *cmd_block)
{
	t_token	*token;
	char	*str;

	token = cmd_block->cmd;
	if (token == NULL)
		return (0);
	str = token->str;
	return ((ft_strcmp(str, "cd") == 0
			|| ft_strcmp(str, "echo") == 0
			|| ft_strcmp(str, "env") == 0
			|| ft_strcmp(str, "exit") == 0
			|| ft_strcmp(str, "export") == 0
			|| ft_strcmp(str, "pwd") == 0
			|| ft_strcmp(str, "unset") == 0));
}
