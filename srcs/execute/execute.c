/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:33 by haeem             #+#    #+#             */
/*   Updated: 2023/09/27 18:32:46 by haeem            ###   ########seoul.kr  */
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
static void	read_heredoc(char *delim, int fd_heredoc, t_hashmap *envmap)
{
	char	*line;	

	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, delim) == 0)
			break ;
		line = replace_dollar(line, envmap);
		if (write(fd_heredoc, line, ft_strlen(line)) < 0)
			msg_exit("read_heredoc() write failed.\n", 1);
		if (write(fd_heredoc, "\n", sizeof(char)) < 0)
			msg_exit("read_heredoc() write failed.\n", 1);
		free(line);
	}
	free(line);
	close(fd_heredoc);
}

static int	get_input_heredoc(
	t_cmd_block	*cmd_block, t_redirect *redirect, t_hashmap *envmap)
{
	int			fd;
	char		*idx_str;
	char		*tmp_file_name;

	idx_str = ft_itoa(cmd_block->idx);
	tmp_file_name = ft_strjoin(".tmp_heredoc_", idx_str);
	free(idx_str);
	fd = open(tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (str_msg_ret("get_heredoc() create file failed. : %s\n",
				tmp_file_name, -1));
	cmd_block->heredoc_file = tmp_file_name;
	read_heredoc(redirect->str, fd, envmap);
	return (0);
}

static int	connect_stdin(t_cmd_block *cmd_block, int *pipes)
{
	int			fd;
	t_list		*p;
	t_redirect	*p_redirect;

	if (cmd_block->redirects_in == NULL && cmd_block->idx != 0)
		dup2(pipes[cmd_block->idx * 2 - 2], STDIN_FILENO);
	p = cmd_block->redirects_in;
	while (p != NULL)
	{
		p_redirect = (t_redirect *)p->content;
		if (p_redirect->type == REDIRECT_HEREDOC)
			fd = open(cmd_block->heredoc_file, O_RDONLY);
		else
			fd = open(p_redirect->str, O_RDONLY);
		if (fd == -1)
			return (str_msg_ret("%s open() failed.\n", p_redirect->str, -1));
		if (p->next == NULL)
			dup2(fd, STDIN_FILENO);
		else
			close(fd);
		p = p->next;
	}
	return (0);
}

static int	connect_stdout(
	t_cmd_block *cmd_block, int num_cmd, int *pipes)
{
	int			fd;
	t_list		*p;
	t_redirect	*p_redirect;

	if (cmd_block->redirects_out == NULL && cmd_block->idx != num_cmd - 1)
		dup2(pipes[cmd_block->idx * 2 + 1], STDOUT_FILENO);
	p = cmd_block->redirects_out;
	while (p != NULL)
	{
		p_redirect = (t_redirect *)p->content;
		if (p_redirect->type == REDIRECT_APPEND)
			fd = open(p_redirect->str, O_WRONLY | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			fd = open(p_redirect->str, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
			return (str_msg_ret("%s open() failed.\n", p_redirect->str, -1));
		if (p->next == NULL)
			dup2(fd, STDOUT_FILENO);
		else
			close(fd);
		p = p->next;
	}
	return (0);
}

/* @Return	SUCCESS = 0
			FAILURE = -1	*/
static int	connect_stdio(
	t_cmd_block *cmd_block, int num_cmd, int *pipes)
{
	if (connect_stdin(cmd_block, pipes) < 0)
		return (-1);
	if (connect_stdout(cmd_block, num_cmd, pipes) < 0)
		return (-1);
	return (0);
}

static int	execute_builtin(t_cmd_block *cmd_block, t_hashmap *envmap)
{
	int	exit;

	exit = 1;
	if (ft_strcmp(cmd_block->cmd->str, "env") == 0)
		exit = builtin_env(envmap);
	else if (ft_strcmp(cmd_block->cmd->str, "pwd") == 0)
		exit = builtin_pwd();
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
	else
		printf("DEBUG : unspecified builtin\n"); //< DEBUG
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
	else if (cmd_block->completed_cmd == NULL)
		msg_exit("DEBUG:NULL execution\n", 1); //< DEBUG. such as "<< a | cat"
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
			printf("\n");
		else if (signo == SIGQUIT)
			printf("Quit: 3\n");
		exitcode = WTERMSIG(exitstatus) + 128;
	}
	str = ft_itoa(exitcode);
	hashmap_insert(envmap, "?", str);
	free(str);
}

static int	free_bzero_ret(char **ptr, int ret)
{
	free(*ptr);
	*ptr = NULL;
	return (ret);
}

int		get_input_heredocs(t_list *cmd_blocks, t_hashmap *envmap)
{
	t_cmd_block	*cmd_block;
	t_list		*p_redirect_in;
	t_redirect	*redirect;

	while (cmd_blocks != NULL)
	{
		cmd_block = (t_cmd_block *)cmd_blocks->content;
		p_redirect_in = (t_list *)cmd_block->redirects_in;
		while (p_redirect_in != NULL)
		{
			redirect = ((t_redirect *)p_redirect_in->content);
			if (redirect->type == REDIRECT_HEREDOC
				&& (get_input_heredoc(cmd_block, redirect, envmap) < 0
				|| (p_redirect_in->next && (unlink(cmd_block->heredoc_file) < 0
				|| free_bzero_ret(&cmd_block->heredoc_file, 0)))))
				return (free_bzero_ret(&cmd_block->heredoc_file, -1));
			p_redirect_in = p_redirect_in->next;
		}
		cmd_blocks = cmd_blocks->next;
	}
	return (0);
}

void	execute(t_list *cmd_blocks, t_hashmap *envmap)
{
	int		*pipes;
	int		num_pipe;
	int		exitcode;
	char	*exit_str;
	int		exitstatus;

	if (cmd_blocks == NULL)
		return ;
	if (get_input_heredocs(cmd_blocks, envmap) < 0)
	{
		hashmap_insert(envmap, "?", "1");
		return ;
	}
	if (is_builtin((t_cmd_block *)cmd_blocks->content)
		&& ft_lstsize(cmd_blocks) == 1)
	{
		// backup original stdio
		int stdin_origin = dup(STDIN_FILENO);
		int stdout_origin = dup(STDOUT_FILENO);
		if (connect_stdio((t_cmd_block *)cmd_blocks->content, 1, NULL) == 0)
		{
			exitcode = execute_builtin((t_cmd_block *)cmd_blocks->content, envmap);
			exit_str = ft_itoa(exitcode);
			hashmap_insert(envmap, "?", exit_str);
			free(exit_str);
		}
		// recover original stdio
		dup2(stdin_origin, STDIN_FILENO);
		dup2(stdout_origin, STDOUT_FILENO);
		close(stdin_origin);
		close(stdout_origin);
		return ;
	}
	num_pipe = ft_lstsize(cmd_blocks) - 1;
	pipes = malloc_open_pipe(ft_lstsize(cmd_blocks));
	signal_default();
	fork_childs(cmd_blocks, pipes, envmap);
	signal_ignore();
	close_pipes(pipes, ft_lstsize(cmd_blocks));
	for (int i = 0; i < ft_lstsize(cmd_blocks); i++)
		waitpid(-1, &exitstatus, 0); //< TODO: change to receive error code  
	insert_exit_status(envmap, exitstatus);
	free(pipes);
}
