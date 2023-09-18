/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:33 by haeem             #+#    #+#             */
/*   Updated: 2023/09/18 21:54:51 by hyunjunk         ###   ########.fr       */
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
		fprintf(stderr, "close() = %d\n", i);
		if (close(pipes[i]) < 0)
		{
			msg_exit("pipe close() failed.\n", 1);
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
		fprintf(stderr, "pipe() = %d * 2 : %d\n", i, 2 * i);
		if (pipe(pipes + (2 * i)) < 0)
		{
			msg_exit("pipe open() failed.\n", 1);
		}
		i++;
	}
	return (pipes);
}

static void	execute_cmd_block(
	t_cmd_block *cmd_block, int num_cmd, int *pipes, char **envp)
{
	int	fd;

	if (cmd_block->redirect_in != NULL)
	{
		// TODO : implement here_doc
		//if (cmd_block->redirect_is_heredoc)
			//fd = redirect_heredoc()
		//else
			fd = open(cmd_block->redirect_in, O_RDONLY);
		if (fd == -1)
			str_msg_exit("%s open() failed.\n", cmd_block->redirect_in, 1);
		dup2(fd, STDIN_FILENO);
	}
	else if (cmd_block->idx != 0)
		dup2(pipes[cmd_block->idx * 2 - 2], STDIN_FILENO);
	if (cmd_block->redirect_out != NULL)
	{
		fd = open(cmd_block->redirect_out, O_WRONLY | O_CREAT | O_TRUNC
				| (O_APPEND & ~(cmd_block->redirect_is_append - 1)),
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
			str_msg_exit("%s open() failed.\n", cmd_block->redirect_out, 1);
		dup2(fd, STDOUT_FILENO);
	}
	else if (cmd_block->idx != num_cmd - 1)
		dup2(pipes[cmd_block->idx * 2 + 1], STDOUT_FILENO);
	close_pipes(pipes, num_cmd);
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
			cmd_block->idx = i;
			execute_cmd_block(cmd_block, ft_lstsize(cmd_blocks), pipes, envp);
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
	for (int i = 0; i < ft_lstsize(cmd_blocks); i++)
		waitpid(-1, NULL, 0); //< TODO: change to receive error code  
}
