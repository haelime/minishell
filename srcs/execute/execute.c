/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:33 by haeem             #+#    #+#             */
/*   Updated: 2023/09/29 13:36:17 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"

static int	execute_builtin(t_cmd_block *cmd_block, t_hashmap *envmap)
{
	int	exit;

	exit = 1;
	if (ft_strcmp(cmd_block->cmd->str, "env") == 0)
		exit = builtin_env(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "pwd") == 0)
		exit = builtin_pwd(envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "export") == 0)
		exit = builtin_export(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "unset") == 0)
		exit = builtin_unset(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "echo") == 0)
		exit = builtin_echo(cmd_block->options);
	else if (ft_strcmp(cmd_block->cmd->str, "cd") == 0)
		exit = builtin_cd(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "exit") == 0)
		exit = builtin_exit(cmd_block->options);
	return (exit);
}

static void	execute_cmd_block(
	t_cmd_block *cmd_block, int num_cmd, int *pipes, t_hashmap *envmap)
{
	if (connect_stdio(cmd_block, num_cmd, pipes) < 0)
		exit(1);
	close_pipes(pipes, num_cmd);
	cmd_block->options[0] = cmd_block->completed_cmd;
	if (cmd_block->cmd == NULL)
		exit(0);
	else if (is_builtin(cmd_block))
		exit(execute_builtin(cmd_block, envmap));
	else if (execve(
			cmd_block->completed_cmd,
			cmd_block->options,
			malloc_get_envp(envmap)) == -1)
		str_msg_exit("%s command not found.\n", cmd_block->options[0], 1);
}

static void	fork_childs(
	t_list *cmd_blocks, int *pipes, t_hashmap *envmap)
{
	int			i;
	pid_t		pid;
	t_list		*p_list;
	t_cmd_block	*cmd_block;

	p_list = cmd_blocks;
	i = -1;
	while (++i < ft_lstsize(cmd_blocks))
	{
		pid = fork();
		if (pid == -1)
			msg_exit("pipe() failed.\n", 1);
		else if (pid == 0)
		{
			cmd_block = (t_cmd_block *)p_list->content;
			cmd_block->completed_cmd = malloc_find_completed_cmd(
					cmd_block->cmd, malloc_get_paths(envmap));
			if (cmd_block->completed_cmd == NULL && cmd_block->cmd != NULL
				&& !is_builtin(cmd_block))
				str_msg_exit("%s: command not found\n", cmd_block->cmd->str, 1);
			cmd_block->idx = i;
			execute_cmd_block(cmd_block, ft_lstsize(cmd_blocks), pipes, envmap);
		}
		p_list = p_list->next;
	}
}

void	execute_single_builtin(t_list *cmd_blocks, t_hashmap *envmap)
{
	int			exitcode;
	char		*exit_str;
	const int	stdin_origin = dup(STDIN_FILENO);
	const int	stdout_origin = dup(STDOUT_FILENO);

	if (connect_stdio((t_cmd_block *)cmd_blocks->content, 1, NULL) == 0)
	{
		exitcode = execute_builtin((t_cmd_block *)cmd_blocks->content, envmap);
		exit_str = ft_itoa(exitcode);
		hashmap_insert(envmap, "?", exit_str);
		free(exit_str);
	}
	dup2(stdin_origin, STDIN_FILENO);
	dup2(stdout_origin, STDOUT_FILENO);
	close(stdin_origin);
	close(stdout_origin);
	return ;
}

void	execute(t_list *cmd_blocks, t_hashmap *envmap)
{
	int		*pipes;
	int		exitstatus;
	int		i;

	if (cmd_blocks == NULL)
		return ;
	if (fork_get_all_heredocs(cmd_blocks, envmap) != 0)
		return ;
	if (is_builtin((t_cmd_block *)cmd_blocks->content)
		&& ft_lstsize(cmd_blocks) == 1)
	{
		execute_single_builtin(cmd_blocks, envmap);
		return ;
	}
	pipes = malloc_open_pipe(ft_lstsize(cmd_blocks));
	signal_default();
	fork_childs(cmd_blocks, pipes, envmap);
	signal_ignore();
	close_pipes(pipes, ft_lstsize(cmd_blocks));
	i = -1;
	while (++i < ft_lstsize(cmd_blocks))
		waitpid(-1, &exitstatus, 0);
	insert_exit_status(envmap, exitstatus);
	free(pipes);
}
