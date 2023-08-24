/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:57:45 by haeem             #+#    #+#             */
/*   Updated: 2023/08/24 22:48:20 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/hashlib.h"
#include "../include/parsetree.h"
#include "../libft/include/libft.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_hashmap	*envmap;
	t_pstree	*pstree;

	input = NULL;
	envmap = hash_envp(envp);
	init_shell(argc, argv, envp, envmap);
	while (1)
	{
		get_input(&input, envmap);
		pstree = parse(input, envmap);
		// execute(pstree, envmap);
	}
	return (0);
}

// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close, fork, wait, waitpid, wait3, wait4, signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat, unlink, execve,
// dup, dup2, pipe, opendir, readdir, closedir,
// strerror, perror, isatty, ttyname, ttyslot, ioctl,
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs