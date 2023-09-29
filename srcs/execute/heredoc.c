/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:29:31 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/09/29 13:36:02 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"

//	Close fd_heredoc by itself
void	read_heredoc(char *delim, int fd_heredoc, t_hashmap *envmap)
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

int	get_input_heredoc(
	t_cmd_block	*cmd_block, t_redirect *redirect, t_hashmap *envmap)
{
	int			fd;

	fd = open(cmd_block->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (str_msg_ret("get_heredoc() create file failed. : %s\n",
				cmd_block->heredoc_file, 1));
	read_heredoc(redirect->str, fd, envmap);
	return (0);
}

int	get_input_heredocs(t_list *cmd_blocks, t_hashmap *envmap)
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
				&& (get_input_heredoc(cmd_block, redirect, envmap) < 0))
				return (1);
			p_redirect_in = p_redirect_in->next;
		}
		cmd_blocks = cmd_blocks->next;
	}
	return (0);
}

/* @return	SUCCESS	(0)
			FAILURE (-1)	*/
int	fork_get_all_heredocs(t_list *cmd_blocks, t_hashmap *envmap)
{
	int		exitstatus;

	signal_ignore();
	if (fork() == 0)
	{
		signal_default();
		exit(get_input_heredocs(cmd_blocks, envmap));
	}
	waitpid(-1, &exitstatus, 0);
	insert_exit_status(envmap, exitstatus);
	if (atoi(hashmap_search(envmap, "?")) != 0)
	{
		hashmap_insert(envmap, "?", "1");
		return (-1);
	}
	return (0);
}
