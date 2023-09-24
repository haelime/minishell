/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:33 by haeem             #+#    #+#             */
/*   Updated: 2023/09/24 17:16:55 by haeem            ###   ########seoul.kr  */
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
		if (pipe(pipes + (2 * i)) < 0)
		{
			msg_exit("pipe open() failed.\n", 1);
		}
		i++;
	}
	return (pipes);
}

//	Close fd_heredoc by itself
static void	read_heredoc(
	t_cmd_block *cmd_block, int fd_heredoc, t_hashmap *envmap)
{
	char	*line;	

	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, cmd_block->redirect_in) == 0)
			break ;
		line = replace_dollar(line, envmap, 1);
		if (write(fd_heredoc, line, ft_strlen(line)) < 0)
			msg_exit("read_heredoc() write failed.\n", 1);
		if (write(fd_heredoc, "\n", sizeof(char)) < 0)
			msg_exit("read_heredoc() write failed.\n", 1);
		free(line);
	}
	free(line);
}

static void	get_heredoc(t_cmd_block	*cmd_block, t_hashmap *envmap)
{
	int			fd;
	char		*idx_str;
	char		*tmp_file_name;

	if (cmd_block->redirect_is_heredoc)
	{
		idx_str = ft_itoa(cmd_block->idx);
		tmp_file_name = ft_strjoin(".tmp_heredoc_", idx_str);
		fd = open(tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd < 0)
			msg_exit("get_heredoc() create file failed.\n", 1);
		free(idx_str);
		cmd_block->heredoc_file = tmp_file_name;
		read_heredoc(cmd_block, fd, envmap);
	}
}

/* @descript	am = append_mask
					IF (is_append) 	THEN 0xFFFFFFFF
					ELSE 			THEN 0x00000000	*/
static void	connect_stdio(t_cmd_block *cmd_block, int num_cmd, int *pipes)
{
	int			fd;
	const int	am = ~(cmd_block->redirect_is_append - 1);

	if (cmd_block->redirect_in != NULL)
	{
		if (cmd_block->redirect_is_heredoc)
			fd = open(cmd_block->heredoc_file, O_RDONLY);
		else
			fd = open(cmd_block->redirect_in, O_RDONLY);
		if (fd == -1)
			str_msg_exit("%s open() failed.\n", cmd_block->redirect_in, 1);
		dup2(fd, STDIN_FILENO);
	}
	else if (cmd_block->idx != 0)
		dup2(pipes[cmd_block->idx * 2 - 2], STDIN_FILENO);
	if (cmd_block->redirect_out != NULL)
	{
		fd = open(cmd_block->redirect_out, O_WRONLY | O_CREAT | (O_TRUNC & ~am)
				| (O_APPEND & am), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
			str_msg_exit("%s open() failed.\n", cmd_block->redirect_out, 1);
		dup2(fd, STDOUT_FILENO);
	}
	else if (cmd_block->idx != num_cmd - 1)
		dup2(pipes[cmd_block->idx * 2 + 1], STDOUT_FILENO);
}

static void	execute_builtin(t_cmd_block *cmd_block, t_hashmap *envmap)
{
	if (ft_strcmp(cmd_block->cmd->str, "env") == 0)
		builtin_env(envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd_block->cmd->str, "export") == 0)
		builtin_export(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "unset") == 0)
		builtin_unset(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "echo") == 0)
		builtin_echo(cmd_block->options);
	else if (ft_strcmp(cmd_block->cmd->str, "cd") == 0)
		builtin_cd(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "exit") == 0)
		builtin_exit(cmd_block->options);
	else
		printf("DEBUG : unspecified builtin\n"); //< DEBUG
	exit(0);
}

static void	execute_cmd_block(
	t_cmd_block *cmd_block, int num_cmd, int *pipes, t_hashmap *envmap)
{
	if (cmd_block->redirect_is_heredoc)
		get_heredoc(cmd_block, envmap);
	connect_stdio(cmd_block, num_cmd, pipes);
	close_pipes(pipes, num_cmd);
	cmd_block->options[0] = cmd_block->completed_cmd;
	if (cmd_block->completed_cmd == NULL)
		msg_exit("DEBUG:NULL execution\n", 1); //< DEBUG. such as "<< a | cat"
	else if (is_builtin(cmd_block))
		execute_builtin(cmd_block, envmap);
	else if (execve(
			cmd_block->completed_cmd,
			cmd_block->options,
			malloc_get_envp(envmap)) == -1)
		str_msg_exit("%s execve() failed.\n", cmd_block->options[0], 1);
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

static void	fork_childs(
	t_list *cmd_blocks, int *pipes, t_hashmap *envmap)
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
			cmd_block->completed_cmd = malloc_find_completed_cmd(
					cmd_block->cmd, malloc_get_paths(envmap));
			if (cmd_block->completed_cmd == NULL && cmd_block->cmd != NULL)
				str_msg_exit("%s not command.\n", cmd_block->cmd->str, 1);
			cmd_block->idx = i;
			execute_cmd_block(cmd_block, ft_lstsize(cmd_blocks), pipes, envmap);
		}
		i++;
		p_list = p_list->next;
	}
}

/* @Summary		Handle builtins that have different behavior when executed alone.
				such as cd, exit, export, unset. 	*/
static void	execute_single_builtin(
	t_cmd_block *cmd_block, t_hashmap *envmap)
{
	if (ft_strcmp(cmd_block->cmd->str, "env") == 0)
		builtin_env(envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd_block->cmd->str, "export") == 0)
		builtin_export(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "unset") == 0)
		builtin_unset(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "echo") == 0)
		builtin_echo(cmd_block->options);
	else if (ft_strcmp(cmd_block->cmd->str, "cd") == 0)
		builtin_cd(cmd_block->options, envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "exit") == 0)
		builtin_exit(cmd_block->options);
	else
		printf("DEBUG : unspecified builtin\n"); //< DEBUG
	return ;
}
void	insert_exit_status(t_hashmap *envmap, int exitstatus)
{
	char	*str;
	int		exitcode;

	exitcode = WEXITSTATUS(exitstatus);
	str = ft_itoa(exitcode);
	hashmap_insert(envmap, "?", str);
	free(str);
}

void	execute(t_list *cmd_blocks, t_hashmap *envmap)
{
	int		*pipes;
	int		num_pipe;
	int		exitstatus;

	if (cmd_blocks == NULL)
		return ;
	if (is_builtin((t_cmd_block *)cmd_blocks->content)
		&& ft_lstsize(cmd_blocks) == 1)
	{
		execute_single_builtin((t_cmd_block *)cmd_blocks->content, envmap);
		return ;
	}
	num_pipe = ft_lstsize(cmd_blocks) - 1;
	pipes = malloc_open_pipe(ft_lstsize(cmd_blocks));
	fork_childs(cmd_blocks, pipes, envmap);
	close_pipes(pipes, ft_lstsize(cmd_blocks));
	waitpid(-1, &exitstatus, 0); //< TODO: change to receive error code  
	insert_exit_status(envmap, exitstatus);
	free(pipes);
}
