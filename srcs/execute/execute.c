/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:33 by haeem             #+#    #+#             */
/*   Updated: 2023/09/18 18:19:28 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"

static void	close_pipes(int *pipes, int num_cmd)
{
	int	i;

	i = 0;
	while (i < (num_cmd - 1) * 2)
	{
		if (close(pipes[i]) < 0)
		{
			exit(1);
		}
		i++;
	}
}

static int	*malloc_open_pipe(int num_cmd)
{
	int	*pipes;
	int	i;

	pipes = malloc(((num_cmd - 1) * 2) * sizeof(int));
	i = 0;
	while (i < num_cmd - 1)
	{
		if (pipe(pipes + (2 * i)) < 0)
		{
			exit(1);
		}
	}
	return (pipes);
}

static void	execute_cmd_block(
	t_cmd_block *cmd_block, int idx, int *pipes, char **envp)
{
	(void)idx;
	(void)pipes;
	cmd_block->options[0] = cmd_block->completed_cmd;
	if (execve(cmd_block->completed_cmd, cmd_block->options, envp) == -1)
		str_msg_exit("%s execve() failed.\n", cmd_block->options[0], 1);
}

static void	fork_childs(
	t_list *cmd_blocks, int *pipes, char **paths, char **envp)
{
	int			i;
	pid_t		pid;
	t_list		*p_list;
	t_cmd_block	*cmd_block;

	p_list = cmd_blocks;
	i = 0;
	while (i < ft_lstsize(cmd_blocks))
	{
		pid = fork();
		if (pid == -1)
			msg_exit("pipe() failed.\n", 1);
		else if (pid == 0)
		{
			cmd_block = (t_cmd_block *)p_list->content;
			cmd_block->completed_cmd
				= malloc_find_completed_cmd(cmd_block->cmd->str, paths);
			if (cmd_block->completed_cmd == NULL)
				str_msg_exit("%s not command.\n", cmd_block->cmd->str, 1);
			execute_cmd_block(cmd_block, i, pipes, envp);
		}
		i++;
		p_list = p_list->next;
	}
}

// @return	IF 		(value does not exist) 	THEN (NULL)
//			ELSE 	(value exists) 			THEN (paths)
char	**get_path_from_env(t_hashmap *envmap)
{
	char	*value;

	value = NULL;
	value = hashmap_search(envmap, "PATH");
	if (value == NULL)
		return (NULL);
	return (ft_split(value, ':'));
}

void	execute(t_list *cmd_blocks, t_hashmap *envmap)
{
	int		*pipes;
	int		num_pipe;
	char	**paths;
	char	**envp;

	if (cmd_blocks == NULL)
		return ;
	paths = get_path_from_env(envmap);
	num_pipe = ft_lstsize(cmd_blocks) - 1;
	pipes = malloc_open_pipe(ft_lstsize(cmd_blocks));
	envp = malloc_get_envp(envmap);
	fork_childs(cmd_blocks, pipes, paths, envp);
	close_pipes(pipes, ft_lstsize(cmd_blocks));
	waitpid(-1, NULL, 0); //< TODO: change to receive error code  
}
