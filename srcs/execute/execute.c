/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:33 by haeem             #+#    #+#             */
/*   Updated: 2023/09/17 18:24:15 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
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
}

static void	fork_childs(t_list *cmd_blocks, char **paths)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < ft_lstsize(cmd_blocks))
	{
		pid = fork();
		if (pid == -1)
			perror_and_exit();
		else if (pid == 0)
			execute_cmd_block();
		i++;
	}
}

// can be NULL
char	**get_path_from_env(t_hashmap *envmap)
{
	char	*value;

	value = NULL;
	value = hashmap_search(envmap, "PATH");
	return (ft_split(value, ":"));
}

void	execute(t_list *cmd_blocks, t_hashmap *envmap)
{
	int		*pipes;
	int		pipenum;
	char	**paths;

	if (cmd_blocks == NULL)
		return ;
	paths = get_path_from_env(envmap);
	pipes = malloc_open_pipe(ft_lstsize(cmd_blocks));
	fork_childs(cmd_blocks, paths);
	close_pipes(pipes, ft_lstsize(cmd_blocks));
}
