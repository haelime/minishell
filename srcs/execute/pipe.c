/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:29:06 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/09/29 13:36:25 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"

void	close_pipes(int *pipes, int num_cmd)
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

int	*malloc_open_pipe(int num_cmd)
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

int	connect_stdin(t_cmd_block *cmd_block, int *pipes)
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

int	connect_stdout(
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
int	connect_stdio(
	t_cmd_block *cmd_block, int num_cmd, int *pipes)
{
	if (connect_stdin(cmd_block, pipes) < 0)
		return (-1);
	if (connect_stdout(cmd_block, num_cmd, pipes) < 0)
		return (-1);
	return (0);
}
