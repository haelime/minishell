/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:33 by haeem             #+#    #+#             */
/*   Updated: 2023/09/17 16:39:41 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"

// void	exec_redirect(t_tree *syntax, t_hashmap *envmap)
// {
// 	t_token	*token;

// 	token = syntax->data;
// 	(void)envmap;
// }

// void	exec_pipe(t_tree *syntax, t_hashmap *envmap)
// {
// 	t_token	*token;

// 	token = syntax->data;
// 	(void)envmap;
// }

// void	exec_subshell(t_tree *syntax, t_hashmap *envmap)
// {
// 	t_token	*token;

// 	token = syntax->data;
// 	(void)envmap;
// }

// void	exec_word(t_tree *syntax, t_hashmap *envmap)
// {
// 	t_token	*token;

// 	token = syntax->data;
// 	(void)envmap;
// }

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
}

static void	fork_childs(t_list *cmd_blocks)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < cb->cmd_num)
	{
		pid = fork();
		if (pid == -1)
			perror_and_exit();
		else if (pid == 0)
			execute_cmd_block();
		i++;
	}
}

void	execute(t_list *cmd_blocks, t_hashmap *envmap)
{
	int		*pipes;
	t_token	*token;

	if (cmd_blocks == NULL)
		return ;
	pipes = malloc_open_pipe(ft_lstsize(cmd_blocks));
	fork_childs(cmd_blocks);
	close_pipes(pipes, ft_lstsize(cmd_blocks));
}
