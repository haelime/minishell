/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:03:36 by haeem             #+#    #+#             */
/*   Updated: 2023/09/17 17:54:46 by haeem            ###   ########seoul.kr  */
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
	str = token->str;
	return ((ft_strcmp(str, "cd") == 0
			|| ft_strcmp(str, "echo") == 0
			|| ft_strcmp(str, "env") == 0
			|| ft_strcmp(str, "exit") == 0
			|| ft_strcmp(str, "export") == 0
			|| ft_strcmp(str, "pwd") == 0
			|| ft_strcmp(str, "unset") == 0));
}
