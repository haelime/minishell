/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:03:36 by haeem             #+#    #+#             */
/*   Updated: 2023/09/29 14:00:28 by hyunjunk         ###   ########.fr       */
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

// bash adds 128 on exit code when exited with signal
void	insert_exit_status(t_hashmap *envmap, int exitstatus)
{
	char	*str;
	int		exitcode;
	int		signo;

	exitcode = 0;
	if (WIFEXITED(exitstatus))
	{
		exitcode = WEXITSTATUS(exitstatus);
	}
	else if (WIFSIGNALED(exitstatus))
	{
		signo = WTERMSIG(exitstatus);
		if (signo == SIGINT)
			str_msg_ret("\n", NULL, 0);
		else if (signo == SIGQUIT)
			str_msg_ret("Quit: 3\n", NULL, 0);
		exitcode = WTERMSIG(exitstatus) + 128;
	}
	str = ft_itoa(exitcode);
	hashmap_insert(envmap, "?", str);
	free(str);
}

// @return	IF 		(value does not exist) 	THEN (NULL)
//			ELSE 	(value exists) 			THEN (paths)
char	**malloc_get_paths(t_hashmap *envmap)
{
	char	*value;

	value = NULL;
	value = hashmap_search(envmap, "PATH");
	if (value == NULL)
		return (NULL);
	return (ft_split(value, ':'));
}
